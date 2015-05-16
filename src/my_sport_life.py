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

@author: martin.dvorak@mindforger.com
'''

import yaml


class MySportLife:
    '''
    Main class.
    '''
        
    def __init__(self):
        self.version = 1.0



class MySportLifeConfiguration:
    '''
    My sport life configuration.
    '''

    def __init__(self, configurationFileName):
        self.configurationFileName = configurationFileName
        stream = open(self.logFileName, 'r')
        self.configuration = yaml.load(stream, Loader=yaml.CLoader)

    def getConfiguration(self):
        return self.configuration


class TrainingLog:
    '''
    Aggregated training logs across all years.
    
    The beauty of Python+YAML is that YAML files are loaded
    to native Python structures (lists, maps, ...). Thus YAML
    drives Python data structures and code here only performs
    traversal and analytics of these structures.    
    '''

    def __init__(self, logFileName):
        self.logFileName = logFileName
        # TODO load all data files declared in config.yaml and merge them
        stream = open(self.logFileName, 'r')
        self.log = yaml.load(stream, Loader=yaml.CLoader)

    def getLog(self):
        return self.log


class ActivityTotals:
    '''
    Total summary for a particular sport activity - used as dictionary value.
    '''
    days = set([]);
    phases = set([]);
    km = 0;
    seconds = 0;


class Report:
    '''
    A class that performs analytics calculation on top of aggregated log.
    '''
    
    daysWorthIt = set([])
    sickDays = set([])
    activityTypes = set([])
    # TODO this must be dictionary and activity has dict with 'km' where its evaluated
    totalConcept2Phases = 0
    totalRunningPhases = 0
    totalConcept2Km = 0
    totalRunningKm = 0

    def __init__(self, data):
        self.data = data

    def calculate(self):
        print 'Calculating year: {}'.format(self.data.get('year'))
        for phase in self.data.get('log'):
            print '  {}'.format(phase.get('date'))
            activity=phase.get('activity')
            if activity == 'sick':
                self.sickDays.add(phase.get('date'))
            else:
                self.daysWorthIt.add(phase.get('date'))
                if activity not in self.activityTypes:
                    self.activityTypes.add(activity)

                if activity == 'Concept2':
                    self.totalConcept2Phases+=1
                    #self.totalConcept2Km += phase.get('distance')

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

    def printStatistics(self):
        # TODO make this single string
        print '\nReport:'
        print '  Active days: {}'.format(len(self.daysWorthIt))
        print '  Sick days: {}'.format(len(self.sickDays))
        print '  Phases: {}'.format(len(self.data.get('log'))-len(self.sickDays))
        print '  Running phases: {}'.format(self.totalRunningPhases)
        print '  Running km: {}'.format(self.totalRunningKm)
        print '  Concept2 phases: {}'.format(self.totalConcept2Phases)
        print '  Concept2 km: {}'.format(self.totalConcept2Km)
        print '\n'


# main()

#log = TrainingLog("config.yaml")
log = TrainingLog('../examples/20-years/2015.yaml')
report = Report(log.getLog())
report.calculate()
report.printStatistics()

# eof
