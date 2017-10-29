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

'''
The beauty of Python+YAML is that YAML files are loaded
to native Python structures (lists, maps, ...). Thus YAML
drives Python trainingLog structures and code here only performs
traversal and analytics of these structures.
'''
import yaml

class Configuration:
    '''
    Configuration.
    '''

    yearFileNames = set({})

    def __init__(self, configurationFileName, colors):
        print '{}Loading configuration...{}'.format(colors['yellow'],colors['end'])
        self.configurationFileName = configurationFileName
        stream = open(self.configurationFileName, 'r')
        self.configuration = yaml.load(stream, Loader=yaml.CLoader)
        print '  Done'

    def getConfiguration(self):
        return self.configuration
    
    def getYearLogFileNames(self):
        for yearFileName in self.configuration.get("inputs"):
            self.yearFileNames.add(yearFileName.get("training-log-file"))
        return self.yearFileNames



class TrainingLog:
    '''
    Aggregated YAML training logs across all years.
    '''

    # all training phases (all years) ordered by time
    phases = []
    # year to list of phases ordered by time
    yearToPhases = {}

    def __init__(self, configuration, trainingLogDirectoryPath, colors):
        print '{}Loading training logs...{}'.format(colors['yellow'],colors['end'])
        for yearFileName in configuration.getYearLogFileNames():
            yearFilePath = trainingLogDirectoryPath+"/"+yearFileName
            print '  {}'.format(yearFileName)
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
        print "  {} log done".format(yearLog.get("year"))
