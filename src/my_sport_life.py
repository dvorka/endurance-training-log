#!/usr/bin/env python

'''
MySportLife, Martin Dvorak, 2015

Licensed under the Apache License, Version 2.0 (the "License"); you may
not use this file except in compliance with the License. You may obtain
a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations
under the License.
'''

import yaml
'''
The beauty of Python+YAML is that YAML files are loaded
to native Python structures (lists, maps, ...). Thus YAML
drives Python trainingLog structures and code here only performs
traversal and analytics of these structures.
'''
import os
from datetime import datetime

'''
Design principles:
   * Self-contained Python file i.e. only single file might be distributed without
     any dependencies and use to generate MSL documentation.
   * MSL may generate defaults e.g. CSS to ~/.msl directory where it can be customed
     by users. 
'''

__version__ = "0.0.1-dev"
__notes__ = "development version"
__author__ = "martin.dvorak@mindforger.com"
__license__ = "Apache License 2.0"
__url__ = "http://github.com/dvorka/my-sport-life"


l10nweekdays = ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"]
l10nmonths = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

class MySportLife:
    '''
    Main class - loads configuration, loads all training log files, aggregates log files
    and generates HTML and/or MySportLife log with analytics.
    '''

    def __init__(self, trainingLogDirectoryPath, outputDirectoryPath):
        self.trainingLogDirectoryPath = trainingLogDirectoryPath
        self.outputDirectoryPath = outputDirectoryPath

    def generate(self):
        configuration = MySportLifeConfiguration(self.trainingLogDirectoryPath+'/config.yaml')
        trainingLog = TrainingLog(configuration, self.trainingLogDirectoryPath)
        report = Report(trainingLog)
        report.calculate()        
        htmlLog = HtmlLogGenerator(self.outputDirectoryPath, report)
        htmlLog.generate()

class MySportLifeException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)


class MySportLifeConfiguration:
    '''
    MySportLife configuration.
    '''

    yearFileNames = set({})

    def __init__(self, configurationFileName):
        self.configurationFileName = configurationFileName
        stream = open(self.configurationFileName, 'r')
        self.configuration = yaml.load(stream, Loader=yaml.CLoader)

    def getConfiguration(self):
        return self.configuration
    
    def getYearLogFileNames(self):
        for yearFileName in self.configuration.get("inputs"):
            self.yearFileNames.add(yearFileName.get("training-log-file"))
        return self.yearFileNames

def rmDirRecursively(directoryToDelete):
    for root, dirs, files in os.walk(directoryToDelete, topdown=False):
        for name in files:
            os.remove(os.path.join(root, name))
        for name in dirs:
            os.rmdir(os.path.join(root, name))
    os.rmdir(directoryToDelete)

    
class TrainingLog:
    '''
    Aggregated training logs across all years.
    '''

    # all training phases (all years) ordered by time
    phases = []
    # year to list of phases ordered by time
    yearToPhases = {}

    def __init__(self, configuration, trainingLogDirectoryPath):
        for yearFileName in configuration.getYearLogFileNames():
            yearFilePath = trainingLogDirectoryPath+"/"+yearFileName
            yearLog = self.loadYearTrainingLogFile(yearFilePath)
            self.mergeYearTrainingLog(yearLog)

    def loadYearTrainingLogFile(self, logFileName):
        self.logFileName = logFileName
        stream = open(self.logFileName, 'r')
        return yaml.load(stream, Loader=yaml.CLoader)

    def mergeYearTrainingLog(self, yearLog):
        print "Processing {} log with {} entries...".format(yearLog["year"], len(yearLog["log"]))
        self.yearToPhases[yearLog["year"]]=yearLog["log"]
        for unit in yearLog["log"]:
            unit["year"] = yearLog.get("year")
            unit["month"] = unit.get("date").split('/')[0]
            unit["day"] = unit.get("date").split('/')[1]
            self.phases.append(unit)
        print "{} log DONE".format(yearLog.get("year"))


class LifetimeActivityTotal:
    '''
    Lifetime summary for a particular sport activity - used as dictionary value.
    '''
    days = set([]);
    phases = [];
    km = 0;
    seconds = 0;

    def __init__(self):
        pass

    def add(self, phase):
        self.days.add(phase.get('date'))
        self.phases.append(phase)
        if 'distance' in phase:
            if phase['distance'].endswith('km'):
                self.km += float(phase['distance'].replace('km',''))
            else:
                raise MySportLifeException('Unknown unit used in distance {}'.format(phase['distance']))
        if 'time' in phase:
            self.seconds=MslTime(phase['time'])


class MslTime:
    '''
    Parse any of the following strings to fields:
      1h3'10.7
      1h4'
      3'10.7
      10.7
      11
      3'
      3'10
      1h3'
      1h
    '''
    
    hours=0
    minutes=0
    seconds=0
    tens=0
    
    def __init__(self, timestring):
        if 'h' in timestring:
            self.hours=int(timestring.split('h')[0])
            hourDone=timestring.split('h')[1]
            if "'" in hourDone:
                self.minutes=int(hourDone.split("'")[0])
                minutesDone=hourDone.split("'")[1]
                if '.' in minutesDone:
                    self.seconds=int(minutesDone.split(".")[0])
                    self.tens=int(minutesDone.split(".")[1])
        else:
            if "'" in timestring:
                self.minutes=int(timestring.split("'")[0])
                minutesDone=timestring.split("'")[1]
                if '.' in minutesDone:
                    self.seconds=int(minutesDone.split(".")[0])
                    self.tens=int(minutesDone.split(".")[1])
            else:
                if '.' in timestring:
                    self.seconds=int(timestring.split(".")[0])
                    self.tens=int(timestring.split(".")[1])
                else:
                    self.seconds=int(timestring)

    def getSeconds(self):
        return self.hours*60*60+self.minutes*60+self.seconds;


class Report:
    '''
    A class that performs analytics calculation on top of aggregated log.
    '''

    # set of days I was exercising
    daysWorthIt = set([])
    # set of days I was sick
    sickDays = set([])
    # set of activity types that can be found in training log 
    activityTypes = set([])
    # activity type to LifetimeActivityTotal
    activities = {}

    # 2005 > Running > 27    
    yearToActivityToTotalKm={}
    # 2005 > 22 > running > 278km (ALL activity represents sum across activities; WEIGHT represents weight)
    yearToWeekNumberToActivityToTotalKm={}
    # TODO datetime.date(2010, 6, 16).isocalendar()[1]

    def __init__(self, trainingLog):
        self.trainingLog = trainingLog

    def getPhasesByDistanceForActivity(self, activity):
        result = []
        self.trainingLog.phases.sort(cmp=self.comparatorPhasesByDistance, reverse=True)
        for unit in self.trainingLog.phases:
            if unit["activity"] == activity:
                result.append(unit)
        return result

    def comparatorPhasesByDistance(self, phaseA, phaseB):
        if "distance" in phaseA:
            if "distance" in phaseB:
                a=str(phaseA.get("distance"))
                b=str(phaseB.get("distance"))
                print "{} {}".format(a,b)
                distanceA=float(a.replace("km",""))
                distanceB=float(b.replace("km",""))    
                if distanceA-distanceB>0:
                    return 1
                else:
                    if distanceA==distanceB:
                        return 0
                    else:
                        return -1            
            else:
                return 1
        else: 
            if "distance" in phaseB:
                return -1
            else:
                return 0
                
    def comparatorUnitsByDate(self, unit1, unit2):
        pass
    def comparatorUnitsByDistance(self, unit1, unit2):
        pass
    def comparatorUnitsByTime(self, unit1, unit2):
        pass
    def comparatorUnitsByFeeling(self, unit1, unit2):
        pass
    def comparatorUnitsByTemperature(self, unit1, unit2):
        pass

    def dateToWeekday(self, year, month, day):
        d = datetime.date(year, month, day)
        return self.l10nweekdays[d.weekday()]

    def calculate(self):
        print 'Processing...'
        for phase in self.trainingLog.phases:
            activity=phase['activity']
            print '  {}/{}/{} {}'.format(phase['year'], phase['month'], phase['day'], activity)
            if activity == 'sick':
                self.sickDays.add(phase.get('date'))
            else:
                self.daysWorthIt.add(phase.get('date'))
                if activity not in self.activityTypes:
                    self.activityTypes.add(activity)
                    self.activities[activity] = LifetimeActivityTotal()
                totals=self.activities.get(activity)
                totals.add(phase)
        # TODO sort activityTypes and activities by km

    # For every piece of equipment evaluate how much 1km cost
    def equipmentCostPerKm(self):
        print 'TBD'

    # For every piece of equipment evaluate how much 1day
    # of ownership cost
    def equipmentCostPerDay(self):
        print 'TBD'

    def byTimeTracksPerActivity(self):
        print 'TBD'
    def byDistanceTracksPerActivity(self):
        print 'TBD'
    def racesPerActivity(self):
        print 'TBD'

    def meDistancePerDayPerActivity(self):
        print 'TBD'
    def meDistancePerDayAllActivities(self):
        print 'TBD'
    def meTotalUnitsForEachActivity(self):
        print 'TBD'

#
# HTML rendering
#

css='''\
/* My Sport Life CSS

 Web 2.0 colors:
  Shiny silver [#EEEEEE]
  Reddit white [#FFFFFF]
  Magnolia Mag.nolia [#F9F7ED]
  Interactive action yellow [#FFFF88]
  Qoop Mint [#CDEB8B]
  Gmail blue [#C3D9FF]
  Shadows Grey [#36393D]
  Mozilla Red [#FF1A00]
  Rollyo Red [#CC0000]
  RSS Orange [#FF7400]
  Techcrunch green [#008C00]
  Newsvine Green [#006E2E]
  Flock Blue [#4096EE]
  Flickr Pink [#FF0084]
  Ruby on Rails Red [#B02B2C]
  Etsy Vermillion [#D15600]
  43 Things Gold [#C79810]
  Writely Olive [#73880A]
  Basecamp Green [#6BBA70]
  Mozilla Blue [#3F4C6B]
  Digg Blue [#356AA0]
  Last.fm Crimson [#D01F3C]
*/

html {
    margin: 0px;
    padding: 0px;
}

body {
    margin: 0px;
    padding: 0px;
    font-family: 'Roboto', sans-serif;
    font-size: 70%;
    background: #000;
    color: #fff;
}

a:link {
  text-decoration: none;
  border-bottom: 1px dotted #aaa;
  color: #fff;
}
a:visited {
  text-decoration: none;
  color: #fff;
}
a:active {
  text-decoration: none;
  color: #fff;
}
a:hover {
  border-bottom: 1px solid #aaa;
  text-decoration: none;
  color: #fff;
}

.msl-mainContainer {
    width: 100%;
}

.msl-lifeTitle {
    font-size: xx-large;
    width: 100%;
    text-align: center;
}

.msl-footer {
    width: 100%;
    text-align: center;
}

/* activities: colors */

.msl-activityRunning {
  background-color: #0066ff;
}
.msl-activityBiking {
  background-color: #006600;
}
.msl-activityConcept2 {
  background-color: #fff;
}
.msl-activitySwimming {
  background-color: #0000ff;
}

/* container: left - menu */


/* container: right */
.msl-rightMainPaneContainer {
  vertical-align: top;
  text-align: center;
}

/* summary */

.msl-tableSummaryLifetime {
  margin-left: auto;
  margin-right: auto;
}

/* year: chart monthly */
.msl-chartYearPageKmMonthly {
  background-color: #000;
  text-align: center;
  margin-left: auto;
  margin-right: auto;
}
.msl-chartYearPageKmMonthlyMonth {
  vertical-align: top;
  text-align: center;
}
.msl-chartYearPageKmMonthlyMonthSegment {
  width: 15px;
}

/* year: chart weekly km */
.msl-chartYearPageKmWeekly {
  background-color: #000;
  margin-left: auto;
  margin-right: auto;
}
.msl-chartYearPageKmWeeklyWeekSegment {
  width: 5px;
}

/* year: chart weekly weight */
.msl-chartYearPageWeightWeekly {
  background-color: #000;
}
.msl-chartYearPageWeightWeeklySegment {
  width: 5px;
  background-color: #aaa;
}

/* year: training calendar */
.msl-yearPageTrainingCalendar {
  vertical-align: top;
  border: 1px solid #222;
  border-collapse: collapse;
  margin-left: auto;
  margin-right: auto;
}
.msl-yearPageTrainingCalendar > tbody > tr > td+td {
  border-left: 1px solid #222;
  border-bottom: 1px solid #222;
}

.msl-calendarSickPhase {
  background-color: #e00;
}
.msl-calendarSauna {
  background-color: #993300;
}
.msl-calendarRacePhase {
  background-color: #e00;
}
.msl-calendarRunningRegenerationPhase {
  background-color: #aaa;
}
.msl-calendarRunningSpeedPhase {
  background-color: #aaa;
}
.msl-calendarRunningTempoPhase {
  background-color: #aaa;
}
.msl-calendarRunningHillsPhase {
  background-color: #aaa;
}
.msl-calendarRunningFartlekPhase {
  background-color: #aaa;
}
.msl-calendarRunningLongPhase {
  background-color: #aaa;
}
.msl-calendarConcept2Phase {
  background-color: #aaa;
}
.msl-calendarConcept2LowSpmPhase {
  background-color: #aaa;
}
.msl-calendarRowingOnWaterPhase {
  background-color: #aaa;
}
.msl-calendarKayakOnWaterPhase {
  background-color: #aaa;
}
.msl-calendarBikingMtbPhase {
  background-color: #006600;
}
.msl-calendarBodyweightExercisePhase {
  background-color: #990099;
}
.msl-calendarWeightliftingPhase {
  background-color: #000099;
}

.msl-notThisYearDay {
  background-color: #222;
}

/* eof */
'''

htmlPagePrefix='''\
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>{} - My Sport Life</title>
    <meta name="description" content="MySportLife is a training log with advanced reporting and analytics."/>
    <meta name="keywords" content="training, log, running, rowing, biking, swimming"/>
    <link href='./style.css' rel='stylesheet' type='text/css'>
    <link rel="shortcut icon" href="./favicon.ico" />
    <link rel="alternate" type="application/atom+xml" title="MySportLife commits on GitHub" href="https://github.com/dvorka/my-sport-life/commits/master.atom">
    <link href='http://fonts.googleapis.com/css?family=Roboto' rel='stylesheet' type='text/css'>
  </head>
<body>

<table class="msl-mainContainer">
  <tr>
'''

htmlLeftMenuPanePrefix='''
    <!-- left menu -->
    <td class="msl-leftMenubarContainer" valign="top">
      <div title="My Sport Life" style="color: #555; height: 50px; font-size: xx-large; text-align: center;"><a style="color: #555;" href="http://www.github.com/dvorka/my-sport-life">MSF</a></div>
      <table class="msl-leftMenuBar">
        <tr><td title="Name, age, equipment, injuries, per ? statistics, motto, photo, ..."><a href="./profile.html">Me</a></td></tr>
        <tr><td><a href="./index.html">Summary</a></td></tr>
        <tr><td><a href="./statistics.html">Statistics</a></td></tr>
        <tr><td><a href="./equipment.html">Equipment</a></td></tr>
        <tr><td><a href="./weight.html">Weight</a></td></tr>
        <tr>
          <td>
            Years:
            <table style="margin-left: 7px">
'''

htmlLeftMenuReports='''
        <tr>
          <td title="Personal Bests">
            PBs:
            <table style="margin-left: 7px">
              <tr><td><a href="./pb-running.html">Running</a></td></tr>
              <tr><td><a href="./pb-concept2.html">Concept2</a></td></tr>
              <tr><td><a href="./pb-mtb.html">MTB</a></td></tr>
            </table>
          </td>
        </tr>
        <tr>
          <td title="Races">
            Races:
            <table style="margin-left: 7px">
              <tr><td><a href="./races-running.html">Running</a></td></tr>
            </table>
          </td>
        </tr>
        <tr>
          <td>
            Phases/km:
            <table style="margin-left: 7px">
            {}
            </table>
          </td>
        </tr>
        <tr>
          <td>
            Phases/time:
            <table style="margin-left: 7px">
              {}
            </table>
          </td>
        </tr>
'''

htmlLeftMenuPaneSuffix='''
      </table>
    </td>
'''

htmlMainPanePrefix='''\
    <td class="msl-rightMainPaneContainer">
'''

htmlPageTitle='''      <div class="msl-lifeTitle">{}</div>'''

#
# ... here comes page body specific for every page ...
#

htmlMainPaneSuffix='''\
    <td/>
  </tr>
'''

htmlPageSuffix='''
  <tr>
    <td colspan="2">
      <div class="msl-footer">
        <a href="http://www.mindforger.com">mindforger.com</a>
        <br>2015
        <br>(cc)
        <br>Generated:&nbsp;{}/{}/{}&nbsp;{}:{}.{}
      </div>
    <td>
  </tr>
</table>

</body>
</html>
'''

#
# Page: All years summary
#

htmlAllYearsSummaryTablePrefix='''
    <table>
    <tr>
      <td>Total</td>
      <td>Running</td>
      <td>Biking</td>
      <td>Rowing</td>
      <td>Skiing</td>
      <td>Swimming</td>
    </tr>
'''

htmlAllYearsSummaryTableSuffix='''
    </table>
'''

#
# Page: Activity by distance
#

class HtmlLogGenerator:

    def __init__(self, targetDirectoryPath, report):
        self.targetDirectoryPath = targetDirectoryPath
        self.report = report

    def generate(self):
        self.clean()
        self.generateFileCss()
        self.generateFileIndex()
        for year in self.report.trainingLog.yearToPhases.keys():
            self.generateFileForYear(year)        
        for activity in self.report.activityTypes:            
            self.generateFileByDistance(activity)

    def clean(self):
        if os.path.isdir(self.targetDirectoryPath) and os.path.exists(self.targetDirectoryPath):
            rmDirRecursively(self.targetDirectoryPath)
        os.mkdir(self.targetDirectoryPath)

    def generateFileCss(self):
        filePath = self.targetDirectoryPath+'/style.css'
        f = open(filePath, "w")
        f.write(css)
        f.close()        

    def generateFileIndex(self):
        filePath = self.targetDirectoryPath+'/index.html'
        f = open(filePath, "w")
        f.write(htmlPagePrefix.format('Summary'))
        self.writeLeftMenu(f)
        f.write(htmlMainPanePrefix)
        f.write(htmlPageTitle.format('Summary'))
        # begin body
        
        self.writeAllYearsSummaryTable(f)
        # TODO per year additive chart
        # TODO per year summary table
        # TODO statistics
        # TODO list of links to report
        
        # end body
        f.write(htmlMainPaneSuffix)
        f.write(htmlPageSuffix.format(datetime.today().year, datetime.today().month, datetime.today().day, datetime.today().hour, datetime.today().minute, datetime.today().second))
        f.close()
        
    def generateFileForYear(self, year):
        filePath = self.targetDirectoryPath+'/year-'+str(year)+'.html'
        f = open(filePath, "w")
        f.write(htmlPagePrefix.format(year))
        self.writeLeftMenu(f)
        f.write(htmlMainPanePrefix)
        f.write(htmlPageTitle.format(year))
        # begin body
        self.writeByMonthCharteForYear(f)
        # end body
        f.write(htmlMainPaneSuffix)
        f.write(htmlPageSuffix.format(datetime.today().year, datetime.today().month, datetime.today().day, datetime.today().hour, datetime.today().minute, datetime.today().second))
        f.close()

    def writeByMonthCharteForYear(self, f):
        f.write('\n       <table class="msl-chartYearPageKmMonthly">')
        # TODO column chart how much
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in l10nmonths:
            f.write('<td>{}</td>'.format(month))
        f.write('\n         </tr>')
        # TODO column chart minimum weiht/month
        f.write('\n       </table>')

    def generateFileByDistance(self, activity):
        filePath = self.targetDirectoryPath+'/phases-by-distance-'+activity.lower()+'.html'
        f = open(filePath, "w")
        f.write(htmlPagePrefix.format(activity+' by Distance'))
        self.writeLeftMenu(f)
        f.write(htmlMainPanePrefix)
        f.write(htmlPageTitle.format(activity+' by Distance'))
        # begin main
        phasesByDistance=self.report.getPhasesByDistanceForActivity(activity)
        f.write("\n      <table>")
        for phase in phasesByDistance:
            f.write('\n          <tr>')
            if "distance" in phase:
                f.write('<td>{}</td>'.format(phase["distance"]))
            else:
                print 'Warning: no distance in phase '+phase["date"]
                f.write('<td></td>')
            if "time" in phase:
                f.write('<td>{}</td>'.format(phase["time"]))
            else:
                f.write('<td></td>')
            if "track" in phase:
                f.write('<td>{}</td>'.format(phase["track"]))
            else:
                f.write('<td></td>')
            f.write('<td>{}/{}/{}</td>'.format(phase["year"], phase["month"], phase["day"]))
            f.write('<td>{}</td>'.format(phase["description"]))
            f.write('</tr>')
        f.write("\n      </table>")
        # end main
        f.write(htmlMainPaneSuffix)
        f.write(htmlPageSuffix.format(datetime.today().year, datetime.today().month, datetime.today().day, datetime.today().hour, datetime.today().minute, datetime.today().second))
        f.close()

    def writeAllYearsSummaryTable(self, f):
        f.write('\n      <table>')
        f.write('\n        <tr>')
        for activityType in self.report.activityTypes:
            f.write('\n          <th>{}</th>'.format(activityType))
        f.write('\n        </tr>')
        f.write('\n        <tr>')
        for activityType in self.report.activityTypes:
            f.write('\n          <td>{}</td>'.format(self.report.activities.get(activityType).km))
        f.write('\n        </tr>')
        f.write('\n      </table>')
    
    def writeLeftMenu(self, f):
        f.write(htmlLeftMenuPanePrefix)
        for year in self.report.trainingLog.yearToPhases.keys():
            f.write('\n              <tr><td><a href="./year-{}.html">{}</a></td></tr>'.format(year, year))
        f.write('\n            </table>')
        f.write('\n          </td>')
        f.write('\n        </tr>')
        htmlActivitiesByKm=''
        htmlActivitiesByTime=''
        for activityType in self.report.activityTypes:
            htmlActivitiesByKm=htmlActivitiesByKm+'\n         <tr><td><a href="./phases-by-distance-'+activityType.lower()+'.html">'+activityType+'</a></td></tr>'
            htmlActivitiesByTime=htmlActivitiesByTime+'\n         <tr><td><a href="./phases-by-time-'+activityType.lower()+'.html">'+activityType+'</a></td></tr>'
        f.write(htmlLeftMenuReports.format(htmlActivitiesByKm, htmlActivitiesByTime))        
        f.write(htmlLeftMenuPaneSuffix)

#
# tests
#

def testMslTime():
    testTimes=["1h","5'","5'10", "5'10.7", "13","1h10'","1h10'5","1h10'6.7"]
    for s in testTimes:
        mslTime=MslTime(s)
        print s+' -> '+str(mslTime.getSeconds()) 

#
# main()
#

#mySportLife = MySportLife('/home/dvorka/p/my-sport-life/github/my-sport-life/test/test-data','/home/dvorka/tmp/20years')
mySportLife = MySportLife('/home/dvorka/p/my-sport-life/github/my-sport-life/examples/20-years','/home/dvorka/tmp/20years')
mySportLife.generate()

# eof
