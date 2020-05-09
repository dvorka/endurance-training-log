/*
 dataset.h     Endurance Training Log dataset editor

 Copyright (C) 2020 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "dataset.h"


namespace etl76 {

using namespace std;

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
    clear();
}

void Dataset::clear()
{
    for(DatasetInstance* i:dataset) {
        delete i;
    }
}

int Dataset::removeInstance(int index) {
    if(index >=0 && static_cast<size_t>(index) < dataset.size()) {
        delete dataset[index];
        dataset.erase(dataset.begin()+index);
        return min(static_cast<size_t>(index), dataset.size());
    } else {
        throw EtlRuntimeException(
            "Dataset index of instance to remove out of range: "+std::to_string(index)
        );
    }
}

void Dataset::switchInstances(int a, int b)
{
    DatasetInstance* x = dataset[a];
    dataset[a] = dataset[b];
    dataset[b] = x;
}

int Dataset::upInstance(int index)
{
    if(dataset.size() >= 2
           && index>=1
           && static_cast<size_t>(index) < dataset.size())
    {
        switchInstances(index-1, index);
        return index-1;
    }
    return -1;
}

int Dataset::downInstance(int index)
{
    if(dataset.size() >= 2
           && index>=0
           && static_cast<size_t>(index+1) < dataset.size())
    {
        switchInstances(index, index+1);
        return index+1;
    }
    return -1;
}

void Dataset::from_csv(const string& file_path)
{
    clear();

    //io::CSVReader<28, io::trim_chars<>, io::double_quote_escape<',','\"'>> in(file_path);
    io::CSVReader<28, io::trim_chars<' '>, io::double_quote_escape<',','\"'>> in(file_path);
    in.read_header(
        io::ignore_extra_column,
        "year",
        "month",
        "day",
        "phase",
        "activity_type",
        "description",
        "commute",
        "total_time_seconds",
        "total_distance_meters",
        "warm_up_time_seconds",
        "warm_up_distance_meters",
        "time_seconds",
        "distance_meters",
        "intensity",
        "repetitions",
        "avg_watts",
        "max_watts",
        "gear",
        "route",
        "gpx_url",
        "calories",
        "cool_down_time_seconds",
        "cool_down_distance_meters",
        "weight",
        "weather",
        "weather_temperature",
        "where",
        "grams_of_fat_burnt"
        // TODO BMI
    );

    unsigned year;
    unsigned month;
    unsigned day;
    unsigned phase;
    string activityType;
    string description;
    unsigned commute;
    unsigned totalTimeSeconds;
    unsigned totalDistanceMeters;
    unsigned warmUpTimeSeconds;
    unsigned warmUpDistanceMeters;
    unsigned timeSeconds;
    unsigned distanceMeters;
    string intensity;
    unsigned repetitions;
    unsigned avgWatts;
    unsigned maxWatts;
    string gear;
    string route;
    string gpxUrl;
    unsigned calories;
    unsigned coolDownTimeSeconds;
    unsigned coolDownDistanceMeters;
    float weight;
    string weather;
    unsigned weatherTemperature;
    string where;
    unsigned gramsOfFatBurnt;

    DatasetInstance* instance;

    while(in.read_row(
      year,
      month,
      day,
      phase,
      activityType,
      description,
      commute,
      totalTimeSeconds,
      totalDistanceMeters,
      warmUpTimeSeconds,
      warmUpDistanceMeters,
      timeSeconds,
      distanceMeters,
      intensity,
      repetitions,
      avgWatts,
      maxWatts,
      gear,
      route,
      gpxUrl,
      calories,
      coolDownTimeSeconds,
      coolDownDistanceMeters,
      weight,
      weather,
      weatherTemperature,
      where,
      gramsOfFatBurnt)
    ) {
        instance = new DatasetInstance{
            year,
            month,
            day,
            phase,
            CategoricalValue{activityType},
            QString::fromStdString(description),
            commute!=0,
            totalTimeSeconds,
            totalDistanceMeters,
            warmUpTimeSeconds,
            warmUpDistanceMeters,
            timeSeconds,
            distanceMeters,
            CategoricalValue{intensity},
            repetitions,
            avgWatts,
            maxWatts,
            CategoricalValue{gear},
            CategoricalValue{route},
            QString::fromStdString(gpxUrl),
            calories,
            coolDownTimeSeconds,
            coolDownDistanceMeters,
            weight,
            CategoricalValue{weather},
            weatherTemperature,
            QString::fromStdString(where),
            gramsOfFatBurnt
         };
        addInstance(instance);
    }
}

bool Dataset::file_exists(const std::string& file_path)
{
  struct stat buffer;
  return (stat(file_path.c_str(), &buffer) == 0);
}

void Dataset::to_csv(const std::string& file_path) const
{
    if(file_exists(file_path)) {
        // clean up
        string tmp_file_path{file_path+".tmp"};
        if(file_exists(tmp_file_path)) {
            remove(tmp_file_path.c_str());
        }
        // if save fails, return back to this file: avoid loosing both old and new
        rename(file_path.c_str(), (file_path+".tmp").c_str());
    }

    // save
    std::ofstream csvFile;
    csvFile.open (file_path);

    csvFile <<
       "year, "
       "month, "
       "day, "
       "phase, "
       "activity_type, "
       "description, "
       "commute, "
       "total_time_seconds, "
       "total_distance_meters, "
       "warm_up_time_seconds, "
       "warm_up_distance_meters, "
       "time_seconds, "
       "distance_meters, "
       "intensity, "
       "repetitions, "
       "avg_watts, "
       "max_watts, "
       "gear, "
       "route, "
       "gpx_url, "
       "calories, "
       "cool_down_time_seconds, "
       "cool_down_distance_meters, "
       "weight, "
       "weather, "
       "weather_temperature, "
       "where, "
       "grams_of_fat_burnt" << endl;

    for(DatasetInstance* instance:dataset) {
        csvFile << instance->toCsv();
    }

    csvFile.close();
}

} // etl76 namespace
