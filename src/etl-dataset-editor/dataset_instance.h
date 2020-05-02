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

#include <vector>

#include <QString>


namespace etl76 {

class CategoricalFeature;

class CategoricalValue
{
private:
    QString value;

    CategoricalFeature* feature;
public:
    CategoricalValue(QString value) {
        this->value = value;
    }

    QString toString() const { return value; }
};


class CategoricalFeature
{
private:
    std::vector<CategoricalValue> values;
};


class DatasetInstance
{
private:
    unsigned year;
    unsigned month;
    unsigned day;

    unsigned phase;

    CategoricalValue activityType;
    // TODO description
    bool commute;

    unsigned totalTimeSeconds;
    unsigned totalDistanceMeters;

    // warm-up
    unsigned warmUpSeconds;
    unsigned warmUpDistanceMeters;

    // phase
    unsigned durationSeconds;
    unsigned distanceMeters;
    CategoricalValue intensity; // easy, regen, LSD, fartlek, tempo, race
    unsigned repetitions;
    unsigned avgWatts;
    unsigned maxWatts;
    CategoricalValue equipment;
    CategoricalValue route;
    QString gpxUrl;
    unsigned calories;

    // cool-down
    unsigned coolDownSeconds;
    unsigned coolDownDistanceMeters;

    float weight;
    CategoricalValue weather;
    float weatherTemperature;
    QString where;

    // calculated
    unsigned gramsOfFatBurn;

public:
    DatasetInstance(
            unsigned year,
            unsigned month,
            unsigned day,
            unsigned phase,
            CategoricalValue activityType,
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
            float weatherTemperature,
            QString where,
            unsigned gramsOfFatBurn
    );
    DatasetInstance(const DatasetInstance&) = delete;
    DatasetInstance(const DatasetInstance&&) = delete;
    DatasetInstance &operator=(const DatasetInstance&) = delete;
    DatasetInstance &operator=(const DatasetInstance&&) = delete;

    unsigned getYear() const { return year; }
    unsigned getMonth() const {return month; }
    unsigned getDay() const { return day; }
    QString getYearMonthDay() const {
        return QString(year).append("/").append(QString(month)).append("/").append(QString(day));
    }
    unsigned getPhase() const { return phase; }
    CategoricalValue getActivityType() const { return activityType; }
    bool getCommute() const { return commute; }
    unsigned getTotalTimeSeconds() const { return totalTimeSeconds; }
    QString getTotalTimeStr() const { return QString(totalTimeSeconds).append("''"); }
    unsigned getTotalDistanceMeters() const { return totalDistanceMeters; }
    QString getTotalDistanceStr() const { return QString(totalDistanceMeters).append("m"); }
    // warm-up
    unsigned getWarmUpSeconds() const { return warmUpSeconds; }
    QString getWarmUpSecondsStr() const;
    unsigned getWarmUpDistanceMeters() const { return warmUpDistanceMeters; }
    QString getWarmUpDistanceStr() const;
    // phase
    unsigned getDurationSeconds() const { return durationSeconds; }
    QString getDurationStr() const { return QString(durationSeconds).append("''"); }
    unsigned getDistanceMeters() { return distanceMeters; }
    QString getDistanceStr() const { return QString(distanceMeters).append("m"); }
    CategoricalValue getIntensity() const { return intensity; }
    unsigned getRepetitions() const { return repetitions; }
    unsigned getAvgWatts() const { return avgWatts; }
    unsigned getMaxWatts() const { return maxWatts; }
    CategoricalValue getEquipment() const { return equipment; }
    CategoricalValue getRoute() const { return route; }
    QString getGpxUrl() const { return gpxUrl; }
    int getCalories() const { return calories; }

    // cool-down
    unsigned getCoolDownSeconds() const { return coolDownSeconds; }
    QString getCoolDownStr() const;
    unsigned getCoolDownDistanceMeters() const { return coolDownDistanceMeters; }
    QString getCoolDownDistanceStr() const;

    float getWeight() const { return weight; }
    QString getWeightStr() const { return QString::number(weight).append("kg"); }
    CategoricalValue getWeather() const { return weather; }
    float getWeatherTemperature() const { return weatherTemperature; }
    QString getWhere() const { return where; }

    // calculated
    unsigned getGramsOfFatBurnt() const { return gramsOfFatBurn; }
    QString getGramsOfFatBurntStr() const { return QString(gramsOfFatBurn).append("g"); }
};

}

#endif // ETL76_DATASET_INSTANCE_H
