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

Code conventions:

  - \""" is used for COMMENTS as it is used by PythonDoc generators
  - ''' is used in the CODE, \""" is used only when string needs 
    to contain ''' (''' and \""" are interchangeable as ' and " are)

Documenation generator:

  - http://www.sphinx-doc.org

"""

# Plan:
# - page for year with details i.e. YAML visualization (days, months, ...)
# - left menu generator
# - home page with summaries
# - importers: Strava trainings, XSL (CSV) to YAML convertor, GSheets to YAML, ...

# help
helpString = '''Endurance training log visualizer and analyzer.

Usage: endurance-training-log.py [OPTION] input-yaml-file output-directory

Startup:
  -h  --help        help
  -v  --version     version

Output:
  -c  --color       use color to highlight output
'''

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

# http://ascii-table.com/ansi-escape-sequences.php 
ESC_RED = ''
ESC_GREEN = ''
ESC_BLUE = ''
ESC_YELLOW = ''
ESC_WHITE = ''
ESC_NO_COLOR = ''

#
# main()
#

if __name__ == "__main__":
    sourceDirectory = None
    targetDirectory = None
    nonOptions = 0
    if len(sys.argv)>1: 
        for a in sys.argv:
            if '-T' == a:
                sourceDirectory='/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/test-data'
                targetDirectory='/home/dvorka/tmp/etl-test-data'
            elif '-TT' == a:
                sourceDirectory='/home/dvorka/Desktop/My/endurance-training-log/test/test-data'
                targetDirectory='/home/dvorka/tmp/etl-test-data'
            elif '--color' == a or '-c' == a:
                ESC_RED="[1;31m"
                ESC_GREEN="[1;32m"
                ESC_BLUE="[1;34m"
                ESC_YELLOW="[1;33m"
                ESC_WHITE="[1;37m"
                ESC_NO_COLOR="[0m"
            elif '--help' == a or '-h' == a:
                print helpString.format()
                quit()
            elif '--version' == a or '-v' == a:
                print "{}".format(__version__)
                quit()
            else:
                nonOptions += 1

        if nonOptions == 2: 
            sourceDirectory=sys.argv[1]
            targetDirectory=sys.argv[2]

        if sourceDirectory is not None and targetDirectory is not None:
            enduranceTrainingLog = EnduranceTrainingLog(
                sourceDirectory,
                targetDirectory,
                {
                    'red': ESC_RED,
                    'green': ESC_GREEN,
                    'blue': ESC_BLUE,
                    'yellow': ESC_YELLOW,
                    'white': ESC_WHITE,
                    'end': ESC_NO_COLOR
                })
            enduranceTrainingLog.generate()
            quit()
        
    print helpString.format()

# eof
