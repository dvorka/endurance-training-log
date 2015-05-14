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
   def loadAndDump(self):
       stream = open("config.yaml", 'r')
       data = yaml.load(stream, Loader=yaml.CLoader)
       #yaml.dump(data, Dumper=yaml.CDumper)
       print yaml.dump(data)


# main()

log = TrainingLog()
log.loadAndDump()

# eof
