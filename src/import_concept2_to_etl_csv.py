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

import datetime

import datatable as dt

from src.import_strava_torben_to_etl_csv import EtlDataset

C2_YEARS = [2009, 2010, 2011, 2012, 2013, 2015, 2016, 2017, 2019, 2020]
FILE_SRC_CSV = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/datasets/"
    "concept2.com/concept2-season-"
)
FILE_DST_CSV_FILE = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/"
    "concept2-training-log-import-"
)

# TODO fix rank
# TODO quote description to avoid problems


class Concept2Dataset:
    """concept2.com dataset exported from training log web.

    Columns description:
    "ID",
        [source]
        concept2:<ID>
    "Date",
        [year, month, day, when]
    "Description",
        [description]
    "Work Time (Formatted)",
    "Work Time (Seconds)",
        [time]
        int(1194.3)
    "Rest Time (Formatted)",
    "Rest Time (Seconds)",
    "Work Distance",
        [distance]
    "Rest Distance",
    "Stroke Rate/Cadence",
        [description]
        if not None then "@24"
    "Stroke Count",
    "Pace",
        [description]
        if not None then "1:59"/500m
    "Avg Watts",
    "Cal/Hour",
    "Total Cal",
        [kcal]
    "Avg Heart Rate",
    "Drag Factor",
        [description]
        if not None then DF"122"
    "Age",
    "Weight",
    "Type",
    "Ranked",
        [intensity]
        if not None then "rank"
    "Comments"
        [description]
        if not None then ("...")

    """

    URL_CONCEPT2_ACTIVITY = "https://log.concept2.com/profile/737678/log/"

    def __init__(self, dataset_path: str):
        self.dataset_path = dataset_path
        self.frame: dt.Frame = dt.fread(dataset_path)

    def __str__(self) -> str:
        result: str = f"Dataset path: {self.dataset_path}\n"
        result = f"{result}Columns:\n"
        for name in self.frame.names:
            result = f"{result}  {name}\n"
        return result

    def to_etl_dataset(self) -> dt.Frame:
        etl_frame: dt.Frame = EtlDataset.get_empty_frame()
        for row in range(self.frame.shape[0]):
            print(f"{row}: {self.frame[row,'ID']}")
            new_row: dict = EtlDataset.get_empty_frame_dict()

            # "2020-03-04 11:34:00"
            date_time_obj = datetime.datetime.strptime(
                self.frame[row, "Date"], "%Y-%m-%d %H:%M:%S"
            )
            new_row["year"] = [date_time_obj.year]
            new_row["month"] = [date_time_obj.month]
            new_row["day"] = [date_time_obj.day]
            new_row["when"] = [
                f"{date_time_obj.hour:02}:{date_time_obj.minute:02}"
                f":{date_time_obj.second:02}"
            ]

            new_row["activity"] = ["rowing"]

            description: str = ""
            cadence = self.frame[row, "Stroke Rate/Cadence"]
            description = f"{description} @{cadence}" if cadence else f"{description}"
            pace = self.frame[row, "Pace"]
            description = f"{description} {pace}/500m" if pace else f"{description}"
            drag = self.frame[row, "Drag Factor"]
            description = f"{description} DF{drag}" if drag else f"{description}"
            comment = self.frame[row, "Comments"]
            description = f"{description} ({comment})" if comment else f"{description}"
            new_row["description"] = [description]

            new_row["distance_meters"] = [int(self.frame[row, "Work Distance"])]
            new_row["time_seconds"] = [int(self.frame[row, "Work Time (Seconds)"])]
            new_row["total_distance_meters"] = new_row["distance_meters"]
            new_row["total_time_seconds"] = new_row["time_seconds"]

            speed: float = float(new_row["distance_meters"][0]) / float(
                new_row["time_seconds"][0]
            ) * 3.6
            new_row["avg_speed"] = [speed]
            new_row["max_speed"] = new_row["avg_speed"]
            new_row["elevation_gain"] = [0]

            avg_watts = self.frame[row, "Avg Watts"]
            new_row["avg_watts"] = [int(avg_watts) if avg_watts else 0]
            new_row["kcal"] = [self.frame[row, "Total Cal"]]
            new_row["commute"] = [False]

            intensity = self.frame[row, "Ranked"]
            new_row["intensity"] = ["rank" if intensity else "fartlek"]

            new_row["gear"] = ["my_concept2_e"]

            new_row["url"] = [
                f"{Concept2Dataset.URL_CONCEPT2_ACTIVITY}{self.frame[row, 'ID']}"
            ]

            new_row["source"] = [f"concept2:{self.frame[row, 'ID']}"]

            etl_frame.rbind(dt.Frame(new_row))

        print(f"Imported frame:\n{etl_frame}")

        return etl_frame


#
# main
#

if __name__ == "__main__":
    for year in C2_YEARS:
        concept2_dataset = Concept2Dataset(
            f"{FILE_SRC_CSV}{year}.csv"
        )
        print(concept2_dataset)
        etl_frame = concept2_dataset.to_etl_dataset()
        etl_frame.to_csv(
            f"{FILE_DST_CSV_FILE}{year}.csv"
        )
