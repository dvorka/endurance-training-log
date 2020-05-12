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

SRC_CSV_FILE = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/datasets/"
    "strava.com/ActivityList.csv"
)
DST_CSV_FILE = (
    "/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/"
    "training-log-strava-import.csv"
)


class EtlDataset:
    """Endurance Training Log dataset."""

    COLUMN_NAMES = [
        "year",
        "month",
        "day",
        "phase",
        "when",
        "activity",
        "description",
        "commute",
        "total_time_seconds",
        "total_distance_meters",
        "warm_up_time_seconds",
        "warm_up_distance_meters",
        "time_seconds",
        "distance_meters",
        "intensity",
        "squats",
        "push_ups",
        "crunches",
        "turtles",
        "calfs",
        "repetitions",
        "avg_speed",
        "max_speed",
        "elevation_gain",
        "avg_watts",
        "max_watts",
        "gear",
        "route",
        "url",
        "kcal",
        "cool_down_time_seconds",
        "cool_down_distance_meters",
        "weight",
        "weather",
        "weather_temperature",
        "where",
        "bmi",
        "grams_of_fat_burnt",
        "source",
    ]

    @staticmethod
    def get_empty_frame_dict() -> dict:
        new_row: dict = EtlDataset.get_empty_row()
        for key in new_row:
            new_row[key] = [new_row[key]]
        return new_row

    @staticmethod
    def get_empty_frame() -> dt.Frame:
        frame = dt.Frame(EtlDataset.get_empty_frame_dict())
        del frame[0, :]
        return frame

    @staticmethod
    def get_empty_row() -> dict:
        return {
            "year": 2020,
            "month": 1,
            "day": 1,
            "phase": 1,
            "when": "12h30m00s",
            "activity": "rest",
            "description": "",
            "commute": False,
            "total_time_seconds": 0,
            "total_distance_meters": 0,
            "warm_up_time_seconds": 0,
            "warm_up_distance_meters": 0,
            "time_seconds": 0,
            "distance_meters": 0,
            "intensity": "fartlek",
            "squats": 0,
            "push_ups": 0,
            "crunches": 0,
            "turtles": 0,
            "calfs": 0,
            "repetitions": 0,
            "avg_speed": 0.0,
            "max_speed": 0.0,
            "elevation_gain": 0,
            "avg_watts": 0,
            "max_watts": 0,
            "gear": "",
            "route": "",
            "url": "",
            "kcal": 0,
            "cool_down_time_seconds": 0,
            "cool_down_distance_meters": 0,
            "weight": 0.0,
            "weather": "",
            "weather_temperature": 0,
            "where": "",
            "bmi": 0.0,
            "grams_of_fat_burnt": 0,
            "source": "import",
        }

    def __init__(self):
        pass


class StravaDataset:
    """strava.com dataset exported using Torben tools: https://github.com/entorb/strava

     Columns description:
          id
              [strava_url, source]
              ID to be used to create Strava URL and source strava:<id>
          type
              [activity]
          x_gear_name
              [gear]
          start_date_local
              [year, month, day, when]
              Date and time in my timezone: 09.05.2020 12:20:00
          x_start_h
          name
              [description]
              The first part of the description (before ///)
          x_min
          x_km
          x_min/km
          km/h
              [avgSpeed]
          x_max_km/h
              [maxSpeed]
          x_mi
          x_min/mi
          x_mph
          x_max_mph
          total_elevation_gain
              [elevation_gain]
          x_elev_m/km
          average_heartrate
          max_heartrate
          average_cadence
          average_watts
              [avgWatts]
          kilojoules
              [kcal}
              1 kilojoule = 0.239005736 kilocalories
          commute
              [commute]
              0 or 1
          private
          visibility
          workout_type
              [intensity]
              None, 0 ... 4 (find out manually)
          x_nearest_city_start
          x_start_locality
          x_end_locality
          x_dist_start_end_km
          start_latlng
          end_latlng
          elev_low
          elev_high
          kudos_count
          comment_count
          achievement_count
          athlete
          athlete_count
          average_speed
          device_watts
          display_hide_heartrate_option
          distance
              [distance]
              km distance: 39195.6 ~ 39196m
          elapsed_time
              [time]
              Time in seconds: 7981 ~ 2h10m33s
          external_id
          flagged
          from_accepted_tag
          gear_id
          has_heartrate
          has_kudoed
          heartrate_opt_out
          location_city
              [where]
              City prefix.
          location_country
              [where]
              Country suffix.
          location_state
          manual
          map
          max_speed
          max_watts
          moving_time
          photo_count
          pr_count
          resource_state
          start_date
          start_latitude
          start_longitude
          suffer_score
          timezone
          total_photo_count
          trainer
          upload_id
          upload_id_str
          utc_offset

    """

    URL_STRAVA_ACTIVITY = "https://www.strava.com/activities/"

    def __init__(self, dataset_path: str):
        self.dataset_path = dataset_path
        self.frame: dt.Frame = dt.fread(SRC_CSV_FILE)

    def __str__(self) -> str:
        result: str = f"Dataset path: {self.dataset_path}\n"
        result = f"{result}Columns:\n"
        for name in self.frame.names:
            result = f"{result}  {name}\n"
        return result

    def to_etl_dataset(self) -> dt.Frame:
        etl_frame: dt.Frame = EtlDataset.get_empty_frame()
        for row in range(self.frame.shape[0]):
            # print(f"{row}: {self.frame[row,'id']}")
            new_row: dict = EtlDataset.get_empty_frame_dict()

            # "09.05.2020 12:20:00"
            date_time_obj = datetime.datetime.strptime(
                self.frame[row, "start_date_local"], "%d.%m.%Y %H:%M:%S"
            )
            new_row["year"] = [date_time_obj.year]
            new_row["month"] = [date_time_obj.month]
            new_row["day"] = [date_time_obj.day]
            new_row["when"] = [
                f"{date_time_obj.hour:02}:{date_time_obj.minute:02}"
                f":{date_time_obj.second:02}"
            ]

            new_row["activity"] = [f"{self.frame[row, 'type']}".lower()]

            new_row["description"] = [f"{self.frame[row, 'name']}".replace(";", ":")]

            new_row["distance_meters"] = [int(self.frame[row, "distance"])]
            new_row["time_seconds"] = [int(self.frame[row, "elapsed_time"])]
            new_row["total_distance_meters"] = new_row["distance_meters"]
            new_row["total_time_seconds"] = new_row["time_seconds"]

            new_row["avg_speed"] = [self.frame[row, "km/h"]]
            new_row["max_speed"] = [self.frame[row, "x_max_km/h"]]
            new_row["elevation_gain"] = [int(self.frame[row, "total_elevation_gain"])]

            avg_watts = self.frame[row, "average_watts"]
            new_row["avg_watts"] = [int(avg_watts) if avg_watts else 0]

            kcal = (
                int(self.frame[row, "kilojoules"] / 4.184)
                if self.frame[row, "kilojoules"]
                else 0
            )
            new_row["kcal"] = [kcal]
            new_row["commute"] = [bool(self.frame[row, "commute"])]

            # TODO new_row["intensity"] = [bool(self.frame[row, 'workout_type'])]

            new_row["gear"] = [
                f"{self.frame[row, 'x_gear_name']}".lower().replace(" ", "_")
            ]

            new_row["url"] = [
                f"{StravaDataset.URL_STRAVA_ACTIVITY}{self.frame[row, 'id']}"
            ]

            new_row["source"] = [f"strava:{self.frame[row, 'id']}"]

            etl_frame.rbind(dt.Frame(new_row))

        print(f"Imported frame:\n{etl_frame}")

        return etl_frame


#
# main
#


strava_dataset = StravaDataset(SRC_CSV_FILE)
etl_frame = strava_dataset.to_etl_dataset()
etl_frame.to_csv(DST_CSV_FILE)
