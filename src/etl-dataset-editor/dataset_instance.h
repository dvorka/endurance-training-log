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
#include <sstream>
#include <vector>

#include <QDateTime>
#include <QString>

#include "exceptions.h"

namespace etl76 {

class CategoricalFeature;

class CategoricalValue
{
private:
    QString value;

    CategoricalFeature* feature;
public:
    explicit CategoricalValue(QString value) {
        this->value = value;
    }
    explicit CategoricalValue(std::string value) {
        this->value = QString::fromStdString(value);
    }

    QString toString() const { return value; }
};


class CategoricalFeature
{
private:
    std::vector<CategoricalValue> values;
};


/**
 * @brief Dataset instance.
 *
 * Guidelines, tips and tricks:
 *
 * - activity 'servis', gear 'kato', description 'chain', phase 0, ...
 *   - resets chain km on bike and enables tracking
 * - activity 'sauna', repetitions 3
 * - activity 'meditation'
 * - activity 'row', intensity 'rank'
 *
 * Adding new dataset column checklist:
 *
 * - DatasetInstance:
 *   - field, constructor, getter/setter
 *   - toString()
 *   - toCsv()
 * - Dataset
 *   - CSV parser
 * - Dialog:
 *   - widgets,
 *   - from/to
 */
class DatasetInstance
{
public:
    static const char* DEFAULT_STR_TIME;
    static const char* DEFAULT_STR_WEIGHT;
    static const char* DEFAULT_STR_METERS;
    static const char* DEFAULT_STR_GRAMS;

    static const char* FORMAT_STR_YMD;
    static const char* FORMAT_STR_TIME;

private:
    // TODO add: when
    // TODO rename: calories > kcal
    // TODO rename: gpx_url > url
    // TODO rename: activity_type > activity

    unsigned year;
    unsigned month;
    unsigned day;

    unsigned when; // when time 00h00m00s

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
    CategoricalValue intensity; // rank, easy, regen, LSD, fartlek, tempo, race, ...
    unsigned squats; // drepy
    unsigned pushUps; // kliky
    unsigned crunches; // lehsedy
    unsigned turtles; // zelvy
    unsigned calfs; // vypony
    unsigned repetitions;
    float avgSpeed;
    float maxSpeed;
    unsigned elevationGain; // elevation gain
    unsigned avgWatts;
    unsigned maxWatts;
    CategoricalValue gear;
    CategoricalValue route;
    QString gpxUrl; // strava.com, mapy.cz GPX, ... URL
    unsigned calories;

    // cool-down
    unsigned coolDownTimeSeconds;
    unsigned coolDownDistanceMeters;

    float weight;
    CategoricalValue weather;
    unsigned weatherTemperature;
    QString where;

    // calculated
    float bmi;
    unsigned gramsOfFatBurnt;

    CategoricalValue source; // strava:<id>, concept2, paper:2003, xls_training_log:1996

    /*
     * dataset
     */

    int datasetIndex;

private:

    static unsigned ymdToItem(QString yearMonthDay, int index, const std::string& field);

public:

    /*
     * parsers
     */

    static unsigned ymdToYear(QString yearMonthDay, const std::string& field);
    static unsigned ymdToMonth(QString yearMonthDay, const std::string& field);
    static unsigned ymdToDay(QString yearMonthDay, const std::string& field);

    static unsigned strTimeToSeconds(QString time, const std::string& field);
    static unsigned strMetersToMeters(QString strMeters, const std::string& field);
    static float strKgToKg(QString strKg, const std::string& field);
    static unsigned strGToG(QString strG, const std::string& field);

    /*
     * dataset
     */

    int getDatasetIndex() {
        return this->datasetIndex;
    }
    void setDatasetIndex(int index) {
        this->datasetIndex = index;
    }

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
            unsigned squats,
            unsigned pushUps,
            unsigned crunches,
            unsigned turtles,
            unsigned calfs,
            unsigned repetitions,
            float avgSpeed,
            float maxSpeed,
            unsigned elevationGain,
            unsigned avgWatts,
            unsigned maxWatts,
            CategoricalValue gear,
            CategoricalValue route,
            QString gpxUrl,
            unsigned calories,
            unsigned coolDownTimeSeconds,
            unsigned coolDownDistanceMeters,
            float weight,
            CategoricalValue weather,
            unsigned weatherTemperature,
            QString where,
            float bmi,
            unsigned gramsOfFatBurnt,
            CategoricalValue source
    );
    DatasetInstance(const DatasetInstance&) = delete;
    DatasetInstance(const DatasetInstance&&) = delete;
    DatasetInstance &operator=(const DatasetInstance&) = delete;
    DatasetInstance &operator=(const DatasetInstance&&) = delete;

    std::string toString();
    std::string toCsv();

    /*
     * getters and setters
     */

    unsigned getYear() const { return year; }
    unsigned getMonth() const {return month; }
    unsigned getDay() const { return day; }
    QString getYearMonthDay() const {
        return QString("%1").arg(year, 2, 10, QChar('0'))
                .append("/")
                .append(QString("%1").arg(month, 2, 10, QChar('0')))
                .append("/")
                .append(QString("%1").arg(day, 2, 10, QChar('0')));
    }
    unsigned getPhase() const { return phase; }
    CategoricalValue getActivityType() const { return activityType; }
    QString getDescription() const { return description; }
    bool getCommute() const { return commute; }
    unsigned getTotalTimeSeconds() const { return totalTimeSeconds; }
    QString getTotalTimeStr() const {
        return QDateTime::fromTime_t(totalTimeSeconds).toUTC().toString(FORMAT_STR_TIME);
    }
    unsigned getTotalDistanceMeters() const { return totalDistanceMeters; }
    QString getTotalDistanceMetersStr() const { return QString::number(totalDistanceMeters).append("m"); }
    // warm-up
    unsigned getWarmUpSeconds() const { return warmUpTimeSeconds; }
    QString getWarmUpTimeStr() const { return QDateTime::fromTime_t(warmUpTimeSeconds).toUTC().toString(FORMAT_STR_TIME); }
    unsigned getWarmUpDistanceMeters() const { return warmUpDistanceMeters; }
    QString getWarmUpDistanceMetersStr() const { return QString::number(warmUpDistanceMeters).append("m"); }
    // phase
    unsigned getTimeSeconds() const { return timeSeconds; }
    QString getTimeStr() const { return QDateTime::fromTime_t(timeSeconds).toUTC().toString(FORMAT_STR_TIME); }
    unsigned getDistanceMeters() { return distanceMeters; }
    QString getDistanceMetersStr() const { return QString::number(distanceMeters).append("m"); }
    CategoricalValue getIntensity() const { return intensity; }
    unsigned getSquats() const { return squats; }
    unsigned getPushUps() const { return pushUps; }
    unsigned getCrunches() const { return crunches; }
    unsigned getTurles() const { return turtles; }
    unsigned getCalfs() const { return calfs; }
    unsigned getRepetitions() const { return repetitions; }
    unsigned getAvgSpeed() const { return avgSpeed; }
    unsigned getMaxSpeed() const { return maxSpeed; }
    unsigned getElevationGain() const { return elevationGain; }
    unsigned getAvgWatts() const { return avgWatts; }
    unsigned getMaxWatts() const { return maxWatts; }
    CategoricalValue getGear() const { return gear; }
    CategoricalValue getRoute() const { return route; }
    QString getGpxUrl() const { return gpxUrl; }
    int getCalories() const { return calories; }

    // cool-down
    unsigned getCoolDownTimeSeconds() const { return coolDownTimeSeconds; }
    QString getCoolDownTimeStr() const { return QDateTime::fromTime_t(coolDownTimeSeconds).toUTC().toString(FORMAT_STR_TIME); }
    unsigned getCoolDownDistanceMeters() const { return coolDownDistanceMeters; }
    QString getCoolDownDistanceStr() const { return QString::number(coolDownDistanceMeters).append("m"); }

    float getWeight() const { return weight; }
    QString getWeightStr() const { return QString::number(weight).append("kg"); }
    CategoricalValue getWeather() const { return weather; }
    unsigned getWeatherTemperature() const { return weatherTemperature; }
    QString getWhere() const { return where; }

    // calculated
    float getBmi() const { return bmi; }
    unsigned getGramsOfFatBurnt() const { return gramsOfFatBurnt; }
    QString getGramsOfFatBurntStr() const { return QString::number(gramsOfFatBurnt).append("g"); }

    CategoricalValue getSource() const { return source; }
};

} // namespace etl76

#endif // ETL76_DATASET_INSTANCE_H
