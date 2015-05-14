#!/usr/bin/env python
#
# MySportLife, Martin Dvorak, 2015
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may
# not use this file except in compliance with the License. You may obtain
# a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations
# under the License.

import yaml



class MySportLife:
   version=1.0


class TrainingPhase:

   def __init__(self):
       print 'Constructor of %d' % self.version

   def dump(self):
       print 'Hi there!'


# The beauty of Python+YAML is that YAML files are loaded
# to native Python structures (lists, maps, ...). Thus YAML
# drives Python datastructures and code here only performs
# traversal and analytics of these structures.
class TrainingLog:
    
    # Load all data files declared in config.yaml
    def load(self):
        print 'TBD'

    def loadAndDump(self):
        stream = open("config.yaml", 'r')
        data = yaml.load(stream, Loader=yaml.CLoader)
        print yaml.dump(data)

class Report:

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


# main()

log = TrainingLog()
log.loadAndDump()

# eof
