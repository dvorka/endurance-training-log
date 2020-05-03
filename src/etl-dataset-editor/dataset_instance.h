/*
 dataset_instance.h     Endurance Training Log dataset editor

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
#ifndef ETL76_DATASET_INSTANCE_H
#define ETL76_DATASET_INSTANCE_H

#include <string>
#include <vector>


namespace etl76 {

class CategoricalFeature;

class CategoricalValue
{
private:
    std::string value;

    CategoricalFeature* feature;
};


class CategoricalFeature
{
private:
    std::vector<CategoricalValue> values;
};


class DatasetInstance
{
private:
    int year;
    int month;
    int day;

    int phase;

    CategoricalValue activityType;
    std::string description;
    bool commute;
    bool race;

    // total = warm + phase + cool
    int totalTimeSeconds;
    int totalDistanceMeters;

    // warm-up
    int warmUpSeconds;
    int warmUpDistanceMeters;

    // phase
    int timeSeconds;
    int distanceMeters;
    CategoricalValue intensity;
    int repetitions;
    int avgWatts;
    int maxWatts;
    CategoricalValue equipment;
    CategoricalValue route;
    std::string gpxUrl;
    int calories;

    // cool-down
    int coolDownSeconds;
    int coolDownDistanceMeters;

    float weight;
    CategoricalValue weather;
    float weatherTemperature;
    std::string where;

    // calculated
    int gramsOfFatBurn;

public:
    DatasetInstance();
    DatasetInstance(const DatasetInstance&) = delete;
    DatasetInstance(const DatasetInstance&&) = delete;
    DatasetInstance &operator=(const DatasetInstance&) = delete;
    DatasetInstance &operator=(const DatasetInstance&&) = delete;

};

}

#endif // ETL76_DATASET_INSTANCE_H

