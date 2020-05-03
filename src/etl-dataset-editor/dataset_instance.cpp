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
#include "dataset_instance.h"


namespace etl76 {

DatasetInstance::DatasetInstance(
        unsigned year,
        unsigned month,
        unsigned day,
        unsigned phase,
        CategoricalValue activityType,
        QString description,
        bool commute,
        unsigned totalTimeSeconds,
        unsigned totalDistanceMeters,
        unsigned warmUpSeconds,
        unsigned warmUpDistanceMeters,
        unsigned durationSeconds,
        unsigned distanceMeters,
        CategoricalValue intensity,
        unsigned repetitions,
        unsigned avgWatts,
        unsigned maxWatts,
        CategoricalValue equipment,
        CategoricalValue route,
        QString gpxUrl,
        unsigned calories,
        unsigned coolDownSeconds,
        unsigned coolDownDistanceMeters,
        float weight,
        CategoricalValue weather,
        unsigned weatherTemperature,
        QString where,
        unsigned gramsOfFatBurn
):
    year(year),
    month(month),
    day(day),
    phase(phase),
    activityType(activityType),
    description(description),
    commute(commute),
    totalTimeSeconds(totalTimeSeconds),
    totalDistanceMeters(totalDistanceMeters),
    warmUpSeconds(warmUpSeconds),
    warmUpDistanceMeters(warmUpDistanceMeters),
    timeSeconds(durationSeconds),
    distanceMeters(distanceMeters),
    intensity(intensity),
    repetitions(repetitions),
    avgWatts(avgWatts),
    maxWatts(maxWatts),
    equipment(equipment),
    route(route),
    gpxUrl(gpxUrl),
    calories(calories),
    coolDownSeconds(coolDownSeconds),
    coolDownDistanceMeters(coolDownDistanceMeters),
    weight(weight),
    weather(weather),
    weatherTemperature(weatherTemperature),
    where(where),
    gramsOfFatBurnt(gramsOfFatBurn)
{}

} // etl76 namespace
