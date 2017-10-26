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

# help
helpString = """Environment Virtualization codestyle checker and enforcer.

Usage codestyle-enforcer.py [OPTION]

Output:
  -h  --help        help
  -c  --color       use color to highlight output
  -l  --link        print paths as URIs to be clickable in terminal like gnome-terminal
"""

import etl-model
import etl-frontend
import etl-kernel
import etl-backend

__version__ = "0.0.1-dev"
__notes__ = "development version"
__author__ = "martin.dvorak@mindforger.com"
__license__ = "Apache License 2.0"
__url__ = "http://github.com/dvorka/endurance-training-log"

# constants
ESC_LIGHT_RED = ''
ESC_LIGHT_GREEN = ''
ESC_YELLOW = ''
ESC_WHITE = ''
ESC_NO_COLOR = ''

#
# My Sport Life
#

class MySportLife:
    '''
    Main class - loads configuration, loads all training log files, aggregates log files
    and generates HTML and/or MySportLife log with analytics.
    '''

    def __init__(self, trainingLogDirectoryPath, outputDirectoryPath):
        self.trainingLogDirectoryPath = trainingLogDirectoryPath
        self.outputDirectoryPath = outputDirectoryPath

    def generate(self):
        print 'Endurance Training Log:\n  {}\n    >>>\n  {}'.format(self.trainingLogDirectoryPath, self.outputDirectoryPath)
        configuration = MySportLifeConfiguration(self.trainingLogDirectoryPath+'/config.yaml')
        trainingLog = TrainingLog(configuration, self.trainingLogDirectoryPath)
        report = Report(trainingLog)
        report.calculate()        
        htmlLog = HtmlLogGenerator(self.outputDirectoryPath, report)
        htmlLog.generate()

#
# main()
#

if len(sys.argv)>1: 
    for a in sys.argv:
        if '--color' == a or '-c' == a:
            ESC_LIGHT_RED="[1;31m"
            ESC_LIGHT_GREEN="[1;32m"
            ESC_YELLOW="[1;33m"
            ESC_WHITE="[1;37m"
            ESC_NO_COLOR="[0m"
        if '--help' == a or '-h' == a:
            print helpString.format(RULE_FILE_JAVA_MAX_LINES, RULE_FILE_JAVA_MAX_LINE_LENGHT, RULE_FILE_POM_MAX_LINE_LENGHT)
            quit()

enduranceTrainingLog = EnduranceTrainingLog('/home/dvorka/p/my-sport-life/github/my-sport-life/test/test-data','/home/dvorka/tmp/20years')
endurancetraininglog.generate()


