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
helpString = """Endurance training log visualizer and analyzer.

Usage: endurance-training-log.py [OPTION] input-yaml-file output-directory

Startup:
  -h  --help        help
  -v  --version     version

Output:
  -c  --color       use color to highlight output
"""

import sys

import etlmodel
import etlfrontend
from etlkernel import EnduranceTrainingLog

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
# main()
#

if len(sys.argv)>1: 
    for a in sys.argv:
        if '-T' == a:
            enduranceTrainingLog = EnduranceTrainingLog(
                '/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/test-data',
                '/home/dvorka/tmp/20years')
            enduranceTrainingLog.generate()
            quit()
        if '--color' == a or '-c' == a:
            ESC_LIGHT_RED="[1;31m"
            ESC_LIGHT_GREEN="[1;32m"
            ESC_YELLOW="[1;33m"
            ESC_WHITE="[1;37m"
            ESC_NO_COLOR="[0m"

            if len(sys.argv)==3: 
                enduranceTrainingLog = EnduranceTrainingLog(sys.argv[1],sys.argv[2])
                enduranceTrainingLog.generate()
                quit()
        if '--help' == a or '-h' == a:
            print helpString.format()
            quit()
        if '--version' == a or '-v' == a:
            print "{}".format(__version__)
            quit()

print helpString.format()
    


