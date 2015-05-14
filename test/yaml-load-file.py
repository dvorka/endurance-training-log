#!/usr/bin/env python

import yaml

stream = open("config.yaml", 'r')
data = yaml.load(stream, Loader=yaml.CLoader)
print yaml.dump(data)

# eof
