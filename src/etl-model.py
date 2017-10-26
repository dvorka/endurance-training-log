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

l10nweekdays = ["Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"]
l10nmonths = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']

'''
The beauty of Python+YAML is that YAML files are loaded
to native Python structures (lists, maps, ...). Thus YAML
drives Python training log structures and code here only 
performs traversal, conversion to data model, validation 
and analytics.
'''
import yaml

class EnduranceTrainingLogException(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
