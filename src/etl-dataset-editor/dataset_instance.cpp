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

using namespace std;

const char* DatasetInstance::DEFAULT_STR_TIME = "00h00m00s";
const char* DatasetInstance::DEFAULT_STR_WEIGHT= "90kg";
const char* DatasetInstance::DEFAULT_STR_METERS= "0m";
const char* DatasetInstance::DEFAULT_STR_GRAMS= "0g";

/*
 * parsers
 */

unsigned DatasetInstance::ymdToItem(QString yearMonthDay, int idx)
{
    // yyyy/mm/dd
    if(yearMonthDay.length()) {
        QStringList ymdList = yearMonthDay.split("/");
        cout << "Y " << ymdList[0].toStdString() << endl;
        cout << "M " << ymdList[1].toStdString() << endl;
        cout << "D " << ymdList[2].toStdString() << endl;
        if(ymdList.length()==3 &&
             ((idx==0 && ymdList[idx].length()==4)
               ||
              (idx>0 && ymdList[idx].length()==2)))
        {
            return ymdList[idx].toUInt();
        }
    }
    return 0;
}

unsigned DatasetInstance::ymdToYear(QString yearMonthDay)
{
    return ymdToItem(yearMonthDay, 0);
}

unsigned DatasetInstance::ymdToMonth(QString yearMonthDay)
{
    return ymdToItem(yearMonthDay, 1);
}

unsigned DatasetInstance::ymdToDay(QString yearMonthDay)
{
    return ymdToItem(yearMonthDay, 2);
}

unsigned DatasetInstance::strTimeToSeconds(QString time)
{
    // 00h00m00s
    if(time.length()==9) {
        if(time.at(2) == 'h' && time.at(5) == 'm' &&time.at(8) == 's') {
            QStringList hourSplit = time.split('h');
            if(hourSplit.length() == 2) {
                unsigned hours = hourSplit[0].toUInt();
                QStringList minSplit = hourSplit[1].split('m');
                if(minSplit.length() == 2) {
                    unsigned mins = minSplit[0].toUInt();
                    unsigned seconds = minSplit[1].toUInt();
                    return hours*3600+mins*60+seconds;
                }
            }
        }
    }
    return 0;
}

unsigned DatasetInstance::strMetersToMeters(QString strMeters)
{
    // 28.000m
    if(strMeters.length()>2 && strMeters.at(strMeters.length()-1) == 'm') {
        strMeters.replace(".", "");
        strMeters.chop(1);
        return strMeters.toUInt();
    }
    return 0;
}

float DatasetInstance::strKgToKg(QString strKg)
{
    // 91.2kg
    if(strKg.length()>2
            && strKg.at(strKg.length()-2) == 'k'
            && strKg.at(strKg.length()-1) == 'g'
            && strKg.contains("."))
    {
        strKg.chop(2);
        return strKg.toFloat();
    }
    return 0;
}

unsigned DatasetInstance::strGToG(QString strG)
{
    // 23g
    if(strG.length()>2 && strG.at(strG.length()-1) == 'g') {
        strG.chop(1);
        return strG.toUInt();
    }
    return 0;
}

/*
 * methods
 */

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
    warmUpTimeSeconds(warmUpTimeSeconds),
    warmUpDistanceMeters(warmUpDistanceMeters),
    timeSeconds(timeSeconds),
    distanceMeters(distanceMeters),
    intensity(intensity),
    repetitions(repetitions),
    avgWatts(avgWatts),
    maxWatts(maxWatts),
    equipment(equipment),
    route(route),
    gpxUrl(gpxUrl),
    calories(calories),
    coolDownTimeSeconds(coolDownTimeSeconds),
    coolDownDistanceMeters(coolDownDistanceMeters),
    weight(weight),
    weather(weather),
    weatherTemperature(weatherTemperature),
    where(where),
    gramsOfFatBurnt(gramsOfFatBurn)
{
    cout << toString();
}

string DatasetInstance::toString()
{
    stringstream os{};
    os << "New dataset instance:" << endl
    << "  Year: " << year << endl
    << "  Month: " << month << endl
    << "  Day: " << day << endl
    << "  Phase: " << phase << endl
    << "  Activity: " << activityType.toString().toStdString() << endl
    << "  Description: " << description.toStdString() << endl
    << "  Commute: " << commute << endl
    << "  Total time: " << totalTimeSeconds << endl
    << "  Total meters: " << totalDistanceMeters << endl
    << "  Warm time: " << warmUpTimeSeconds << endl
    << "  Warm meters: " << warmUpDistanceMeters << endl
    << "  Time: " << timeSeconds << endl
    << "  Meters: " << distanceMeters << endl
    << "  Intensity: " << intensity.toString().toStdString() << endl
    << "  Repetitions: " << repetitions << endl
    << "  Avg watts: " << avgWatts << endl
    << "  Max watts: " << maxWatts << endl
    << "  Equipment: " << equipment.toString().toStdString() << endl
    << "  Route: " << route.toString().toStdString() << endl
    << "  GPX: " << gpxUrl.toStdString() << endl
    << "  Calories: " << calories << endl
    << "  Cool time: " << coolDownTimeSeconds << endl
    << "  Cool meters: " << coolDownDistanceMeters << endl
    << "  Weight: " << weight << endl
    << "  Weather: " << weather.toString().toStdString() << endl
    << "  Temperature: " << weatherTemperature << endl
    << "  Where: " << where.toStdString() << endl
    << "  Fat: " << gramsOfFatBurnt << endl;

    return os.str();
}

string DatasetInstance::toCsv()
{
    stringstream os{};
    os
    << year << ", "
    << month << ", "
    << day << ", "
    << phase << ", "
    << "\"" << activityType.toString().toStdString() << "\", "
    << "\"" << description.toStdString() << "\", "
    << commute << ", "
    << totalTimeSeconds << ", "
    << totalDistanceMeters << ", "
    << warmUpTimeSeconds << ", "
    << warmUpDistanceMeters << ", "
    << timeSeconds << ", "
    << distanceMeters << ", "
    << intensity.toString().toStdString() << ", "
    << repetitions << ", "
    << avgWatts << ", "
    << maxWatts << ", "
    << equipment.toString().toStdString() << ", "
    << route.toString().toStdString() << ", "
    << gpxUrl.toStdString() << ", "
    << calories << ", "
    << coolDownTimeSeconds << ", "
    << coolDownDistanceMeters << ", "
    << weight << ", "
    << weather.toString().toStdString() << ", "
    << weatherTemperature << ", "
    << where.toStdString() << ", "
    << gramsOfFatBurnt << endl;

    return os.str();
}

} // etl76 namespace
