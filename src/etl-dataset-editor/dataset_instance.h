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

#include <iostream>
#include <vector>

#include <QDateTime>
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
public:
    static const char* DEFAULT_STR_TIME;
    static const char* DEFAULT_STR_WEIGHT;
    static const char* DEFAULT_STR_METERS;
    static const char* DEFAULT_STR_GRAMS;

private:
    unsigned year;
    unsigned month;
    unsigned day;

    unsigned phase;

    CategoricalValue activityType; // Strava compliant activity identifiers: ride, run, ...
    QString description;
    bool commute;

    // total = warm + phase + cool
    unsigned totalTimeSeconds;
    unsigned totalDistanceMeters;

    // warm-up
    unsigned warmUpTimeSeconds;
    unsigned warmUpDistanceMeters;

    // phase
    unsigned timeSeconds;
    unsigned distanceMeters;
    CategoricalValue intensity; // easy, regen, LSD, fartlek, tempo, race, ...
    unsigned repetitions;
    unsigned avgWatts;
    unsigned maxWatts;
    CategoricalValue equipment;
    CategoricalValue route;
    QString gpxUrl;
    unsigned calories;

    // cool-down
    unsigned coolDownTimeSeconds;
    unsigned coolDownDistanceMeters;

    float weight;
    CategoricalValue weather;
    float weatherTemperature;
    QString where;

    // calculated
    unsigned gramsOfFatBurnt;

private:

    static unsigned ymdToItem(QString yearMonthDay, int index);

public:

    /*
     * parsers
     */

    static unsigned ymdToYear(QString yearMonthDay);
    static unsigned ymdToMonth(QString yearMonthDay);
    static unsigned ymdToDay(QString yearMonthDay);

    static unsigned strTimeToSeconds(QString time);
    static unsigned strMetersToMeters(QString strMeters);
    static float strKgToKg(QString strKg);
    static unsigned strGToG(QString strG);

public:
    DatasetInstance(
            unsigned year,
            unsigned month,
            unsigned day,
            unsigned phase,
            CategoricalValue activityType,
            QString description,
            bool commute,
            unsigned totalTimeSeconds,
            unsigned totalDistanceMeters,
            unsigned warmUpTimeSeconds,
            unsigned warmUpDistanceMeters,
            unsigned timeSeconds,
            unsigned distanceMeters,
            CategoricalValue intensity,
            unsigned repetitions,
            unsigned avgWatts,
            unsigned maxWatts,
            CategoricalValue equipment,
            CategoricalValue route,
            QString gpxUrl,
            unsigned calories,
            unsigned coolDownTimeSeconds,
            unsigned coolDownDistanceMeters,
            float weight,
            CategoricalValue weather,
            unsigned weatherTemperature,
            QString where,
            unsigned gramsOfFatBurnt
    );
    DatasetInstance(const DatasetInstance&) = delete;
    DatasetInstance(const DatasetInstance&&) = delete;
    DatasetInstance &operator=(const DatasetInstance&) = delete;
    DatasetInstance &operator=(const DatasetInstance&&) = delete;

    void toString();

    /*
     * getters and setters
     */

    unsigned getYear() const { return year; }
    unsigned getMonth() const {return month; }
    unsigned getDay() const { return day; }
    QString getYearMonthDay() const {
        return QString::number(year)
                .append("/")
                .append(QString::number(month))
                .append("/")
                .append(QString::number(day));
    }
    unsigned getPhase() const { return phase; }
    CategoricalValue getActivityType() const { return activityType; }
    QString getDescription() const { return description; }
    bool getCommute() const { return commute; }
    unsigned getTotalTimeSeconds() const { return totalTimeSeconds; }
    QString getTotalTimeStr() const {
        return QDateTime::fromTime_t(totalTimeSeconds).toUTC().toString("hh:mm:ss");
    }
    unsigned getTotalDistanceMeters() const { return totalDistanceMeters; }
    QString getTotalDistanceStr() const { return QString::number(totalDistanceMeters).append("m"); }
    // warm-up
    unsigned getWarmUpSeconds() const { return warmUpTimeSeconds; }
    QString getWarmUpSecondsStr() const;
    unsigned getWarmUpDistanceMeters() const { return warmUpDistanceMeters; }
    QString getWarmUpDistanceStr() const;
    // phase
    unsigned getDurationSeconds() const { return timeSeconds; }
    QString getDurationStr() const { return QString::number(timeSeconds).append("''"); }
    unsigned getDistanceMeters() { return distanceMeters; }
    QString getDistanceStr() const { return QString::number(distanceMeters).append("m"); }
    CategoricalValue getIntensity() const { return intensity; }
    unsigned getRepetitions() const { return repetitions; }
    unsigned getAvgWatts() const { return avgWatts; }
    unsigned getMaxWatts() const { return maxWatts; }
    CategoricalValue getEquipment() const { return equipment; }
    CategoricalValue getRoute() const { return route; }
    QString getGpxUrl() const { return gpxUrl; }
    int getCalories() const { return calories; }

    // cool-down
    unsigned getCoolDownSeconds() const { return coolDownTimeSeconds; }
    QString getCoolDownStr() const;
    unsigned getCoolDownDistanceMeters() const { return coolDownDistanceMeters; }
    QString getCoolDownDistanceStr() const;

    float getWeight() const { return weight; }
    QString getWeightStr() const { return QString::number(weight).append("kg"); }
    CategoricalValue getWeather() const { return weather; }
    unsigned getWeatherTemperature() const { return weatherTemperature; }
    QString getWhere() const { return where; }

    // calculated
    unsigned getGramsOfFatBurnt() const { return gramsOfFatBurnt; }
    QString getGramsOfFatBurntStr() const { return QString::number(gramsOfFatBurnt).append("g"); }
};

} // namespace etl76

#endif // ETL76_DATASET_INSTANCE_H
