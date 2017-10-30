#!/usr/bin/env python
"""
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
"""

import json
from datetime import date, datetime

from etlfrontend import Configuration,TrainingLog
from etlbackend import NEWHtmlLogGenerator

UNKNOWN_WEIGHT = 1024.0

class EnduranceTrainingLog:
    """
    Main class - loads configuration, loads all training log files, aggregates log files
    and generates HTML and/or log with analytics.
    """

    def __init__(self, trainingLogDirectoryPath, outputDirectoryPath, colors):
        self.trainingLogDirectoryPath = trainingLogDirectoryPath
        self.outputDirectoryPath = outputDirectoryPath
        self.colors = colors

    def generate(self):
        print '{}Processing YAML to HTML:{}\n  {}\n    >\n  {}'.format(
            self.colors['green'],
            self.colors['end'],
            self.trainingLogDirectoryPath, 
            self.outputDirectoryPath)
        configuration = Configuration(self.trainingLogDirectoryPath+'/config.yaml', self.colors)
        trainingLog = TrainingLog(configuration, self.trainingLogDirectoryPath, self.colors)
        report = Report(trainingLog, self.colors)
        report.calculate()        
        htmlLog = NEWHtmlLogGenerator(self.outputDirectoryPath, report, self.colors)
        htmlLog.generate()



class LifetimeActivityTotal:
    """
    Lifetime summary for a particular sport activity - used as dictionary value.
    """
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
    """
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
    """
    
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
    """
    A class that performs analytics calculation on top of aggregated log.

    Training log w/ units is kept RAW i.e. YAML format is just converted to Python dicts/arrays.
    Summary and analytics is stored in classes and their field values are calculated 
    by traversing raw training log.   
    """

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
    # 2005 > 3 > Running > 278km (ALL activity represents SUM across activities; WEIGHT represents AVG)
    yearToMonthToActivityToKmTimeWeight={}
    # 2005 > 22 > Running > 278km (ALL activity represents SUM across activities; WEIGHT represents AVG)
    yearToWeekNumberToActivityToKmTimeWeight={}

    def __init__(self, trainingLog, colors):
        self.trainingLog = trainingLog
        self.colors = colors

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

    def distanceFieldToKm(self, s):
        return float(s.replace('km',''))
    def weightFieldToKg(self, s):
        return float(s.replace('kg',''))

    def calculate(self):
        print 'Processing all {} phases...'.format(len(self.trainingLog.phases))
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

                if phase['year'] not in self.yearToActivityToTotalKm:
                    self.yearToActivityToTotalKm[phase['year']]={}
                    self.yearToActivityToTotalKm[phase['year']]['weight-min']=UNKNOWN_WEIGHT
                    self.yearToActivityToTotalKm[phase['year']]['weight-max']=0.0
                if phase['activity'] not in self.yearToActivityToTotalKm[phase['year']]:
                    self.yearToActivityToTotalKm[phase['year']][phase['activity']]={'distance': 0.0, 'time': 0}

                if phase['year'] not in self.yearToMonthToActivityToKmTimeWeight:
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']]={}
                if phase['month'] not in self.yearToMonthToActivityToKmTimeWeight[phase['year']]:
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]={}
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-min']=UNKNOWN_WEIGHT
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-max']=0.0
                if phase['activity'] not in self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]:
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']][phase['activity']]={'distance': 0.0, 'time': 0}

                if phase['year'] not in self.yearToWeekNumberToActivityToKmTimeWeight:
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']]={}

                weeknumber = date(int(phase['year']), int(phase['month']), int(phase['day'])).isocalendar()[1]
                if weeknumber not in self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']]:                        
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]={}
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-min']=UNKNOWN_WEIGHT
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-max']=0.0
                if phase['activity'] not in self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]:
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber][phase['activity']]={'distance': 0.0, 'time': 0}

                if 'distance' in phase:
                    # TODO calculate km once
                    self.yearToActivityToTotalKm[phase['year']][phase['activity']]['distance']+=self.distanceFieldToKm(phase['distance'])
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']][phase['activity']]['distance'] \
                        += self.distanceFieldToKm(phase['distance'])
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber][phase['activity']]['distance'] \
                        += self.distanceFieldToKm(phase['distance'])
                if 'time' in phase:
                    # TODO calculate secs once
                    self.yearToActivityToTotalKm[phase['year']][phase['activity']]['time']+=MslTime(phase['time']).getSeconds()                    
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']][phase['activity']]['time'] \
                        += MslTime(phase['time']).getSeconds()
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber][phase['activity']]['time'] \
                        += MslTime(phase['time']).getSeconds()
                if 'weight' in phase:
                    phaseWeight = self.weightFieldToKg(phase['weight'])
                    self.yearToActivityToTotalKm[phase['year']]['weight-min'] \
                        = min(phaseWeight,self.yearToActivityToTotalKm[phase['year']]['weight-min'])
                    self.yearToActivityToTotalKm[phase['year']]['weight-max'] \
                        = max(phaseWeight,self.yearToActivityToTotalKm[phase['year']]['weight-max'])
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-min'] \
                        = min(phaseWeight,self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-min'])
                    self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-max'] \
                        = max(phaseWeight,self.yearToMonthToActivityToKmTimeWeight[phase['year']][phase['month']]['weight-max'])
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-min'] \
                        = min(phaseWeight,self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-min'])
                    self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-max'] \
                        = max(phaseWeight,self.yearToWeekNumberToActivityToKmTimeWeight[phase['year']][weeknumber]['weight-max'])

        print '\n{}Totals (km) per year per activity:{}'.format(self.colors['yellow'],self.colors['end'])
        print json.dumps(self.yearToActivityToTotalKm, indent=2)
        print '\n{}Totals (km/time/weight) per year per MONTH per activity:{}'.format(self.colors['yellow'],self.colors['end'])
        print json.dumps(self.yearToMonthToActivityToKmTimeWeight, indent=2)
        print '\n{}Totals (km/time/weight) per year per WEEK per activity:{}'.format(self.colors['yellow'],self.colors['end'])
        print json.dumps(self.yearToWeekNumberToActivityToKmTimeWeight, indent=2)

    # For every piece of equipment calculate how much 1 km cost
    def equipmentCostPerKm(self):
        print 'TBD'

    # For every piece of equipment calculate how much 1 day cost
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
