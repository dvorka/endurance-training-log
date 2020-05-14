#!/usr/bin/env python
#
# Endurance Training Log
#
# Copyright (C) 2020 Martin Dvorak <martin.dvorak@mindforger.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

import pandas as pd

C2_YEARS = [2009, 2010, 2011, 2012, 2013, 2015, 2016, 2017, 2019, 2020]
FILE_SRC_CSV = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/"
    "concept2-training-log-import-"
)
FILE_SRC_STRAVA = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/"
    "strava-training-log-import.csv"
)
FILE_DST_CSV_FILE = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/"
    "training-log-days.csv"
)

if __name__ == "__main__":
    interesting_files = [FILE_SRC_STRAVA]
    for year in C2_YEARS:
        interesting_files.append(f"{FILE_SRC_CSV}{year}.csv")
    df = pd.concat((pd.read_csv(f, header=0) for f in interesting_files), sort=False)
    df.to_csv(FILE_DST_CSV_FILE)
