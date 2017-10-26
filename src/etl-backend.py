#!/usr/bin/env python

'''
EnduranceTrainingLog, Martin Dvorak, 2017

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
        print '\nBuilding HTML site...'
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

    def writePageEnd(self, f):
        f.write(htmlMainPaneSuffix)
        f.write(htmlPageSuffix.format(datetime.today().year, datetime.today().month, datetime.today().day, datetime.today().hour, datetime.today().minute, datetime.today().second))

    def generateFileIndex(self):
        filePath = self.targetDirectoryPath+'/index.html'
        print 'Generating {}...'.format(filePath)
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
        self.writePageEnd(f)
        f.close()
        
    def generateFileForYear(self, year):
        filePath = self.targetDirectoryPath+'/year-'+str(year)+'.html'
        print 'Generating {}...'.format(filePath)
        f = open(filePath, "w")
        f.write(htmlPagePrefix.format(year))
        self.writeLeftMenu(f)
        f.write(htmlMainPanePrefix)
        f.write(htmlPageTitle.format(year))
        # begin body
        self.writeByMonthChartForYear(f,year)
        # end body
        self.writePageEnd(f)
        f.close()

    def writeActivitiesChartColumnForMonth(self, year, month):
        if year in self.report.yearToMonthToActivityToKmTimeWeight:
            for activity in self.report.yearToMonthToActivityToKmTimeWeight[year]:
                if 'distance' in self.report.yearToMonthToActivityToKmTimeWeight[year][activity]:
                    km=self.report.yearToMonthToActivityToKmTimeWeight[year][activity]['distance']
                    height=self.report.yearToMonthToActivityToKmTimeWeight[year][activity]['distance']
                    result='<div title="{}: {}km" class="msl-chartYearPageKmMonthlyMonthSegment msl-activityRunning" style="height: {}px;"></div>'.format(activity,km,height)             
                    #              <div title="Concept2: 44km" class="msl-chartYearPageKmMonthlyMonthSegment msl-activityConcept2" style="height: 5px;"></div>
                    #              <div title="Biking: 85km" class="msl-chartYearPageKmMonthlyMonthSegment msl-activityBiking" style="height: 5px;"></div>
                    return result
        return '...'
    
    def writeWeightChartColumnForMonth(self, year, month):
        # TODO self.report.getMinWeight(year,m)
        # min weight, max weight, chart showing min/max delta (green/red if I was getting fat/slimming) 
        return 'TBD'.format(month)

    def writeByMonthChartForYear(self, f, year):
        f.write('\n       <table class="msl-chartYearPageKmMonthly">')
        # activities split columns chart         
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in range(1,12):
            f.write('\n           <td valign="bottom" align="center">{}</td>'.format(self.writeActivitiesChartColumnForMonth(year,month)))
        f.write('\n         </tr>')
        # month total
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in range(1,12):
            # TODO f.write('<td>{}</td>'.format(self.report.getTotalForMonth(year,m)))
            f.write('<td>123</td>')
            pass            
        f.write('\n         </tr>')        
        # month name
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in l10nmonths:
            f.write('<td>{}</td>'.format(month))
        f.write('\n         </tr>')
        # weight min
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in range(1,12):
            # valign="bottom" align="center"
            # TODO f.write('<td>{}</td>'.format(self.report.getTotalForMonth(year,m)))
            f.write('<td>85.4</td>')
            pass            
        f.write('\n         </tr>')        
        # weight chart
        f.write('\n         <tr>')
        f.write('\n           ')
        for month in range(1,12):
            f.write('<td>{}</td>'.format(self.writeWeightChartColumnForMonth(year, month)))
        f.write('\n         </tr>')
        f.write('\n       </table>')

    def generateFileByDistance(self, activity):
        filePath = self.targetDirectoryPath+'/phases-by-distance-'+activity.lower()+'.html'
        print 'Generating {}...'.format(filePath)
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
                print '  Warning: no distance in phase {}/{}'.format(phase['year'], phase["date"])
                f.write('<td>0km</td>')
            if "time" in phase:
                f.write('<td>{}</td>'.format(phase["time"]))
            else:
                f.write("<td>00h00'0</td>")
            if "track" in phase:
                f.write('<td>{}</td>'.format(phase["track"]))
            else:
                f.write('<td>-</td>')
            f.write('<td>{}/{}/{}</td>'.format(phase["year"], phase["month"], phase["day"]))
            f.write('<td>{}</td>'.format(phase["description"]))
            f.write('</tr>')
        f.write("\n      </table>")
        # end main        
        self.writePageEnd(f)
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
