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
const char* DatasetInstance::DEFAULT_STR_WEIGHT = "91.9kg";
const char* DatasetInstance::DEFAULT_STR_METERS = "0m";
const char* DatasetInstance::DEFAULT_STR_GRAMS = "0g";

const char* DatasetInstance::FORMAT_STR_YMD = "yyyy/mm/dd";
const char* DatasetInstance::FORMAT_STR_TIME = "hh'h'mm'm'ss's'";

/*
 * parsers
 */

unsigned DatasetInstance::ymdToItem(QString yearMonthDay, int idx, const string& field)
{
    // yyyy/mm/dd
    if(yearMonthDay.length()) {
        QStringList ymdList = yearMonthDay.split("/");
        if(ymdList.length()==3 &&
             ((idx==0 && ymdList[idx].length()==4)
               ||
              (idx>0 && ymdList[idx].length()==2)))
        {
            return ymdList[idx].toUInt();
        } else {
            throw EtlUserException{""+field+": Invalid year/month/day format - it must be: "+FORMAT_STR_YMD};
        }
    } else {
        throw EtlUserException{""+field+": Empty year/month/day string - it must be: "+FORMAT_STR_YMD};
    }
}

unsigned DatasetInstance::ymdToYear(QString yearMonthDay, const string& field)
{
    return ymdToItem(yearMonthDay, 0, field);
}

unsigned DatasetInstance::ymdToMonth(QString yearMonthDay, const string& field)
{
    return ymdToItem(yearMonthDay, 1, field);
}

unsigned DatasetInstance::ymdToDay(QString yearMonthDay, const string& field)
{
    return ymdToItem(yearMonthDay, 2, field);
}

unsigned DatasetInstance::strTimeToSeconds(QString time, const string& field)
{
    // 00h00m00s
    if(time.length()==9) {
        if(time.at(2) == 'h' && time.at(5) == 'm' && time.at(8) == 's') {
            QStringList hourSplit = time.split('h');
            if(hourSplit.length() == 2) {
                unsigned hours = hourSplit[0].toUInt();
                QStringList minSplit = hourSplit[1].split('m');
                if(minSplit.length() == 2) {
                    minSplit[1].chop(1);
                    unsigned mins = minSplit[0].toUInt();
                    unsigned seconds = minSplit[1].toUInt();
                    return hours*3600+mins*60+seconds;
                } else {
                    throw EtlUserException{""+field+" ("+time.toStdString()+"): Invalid minutes/seconds format - it must be: "+FORMAT_STR_TIME};
                }
            } else {
                throw EtlUserException{""+field+" ("+time.toStdString()+"): Invalid hour format - it must be: "+FORMAT_STR_TIME};
            }
        } else {
            throw EtlUserException{""+field+" ("+time.toStdString()+"): Invalid time format - it must be: "+FORMAT_STR_TIME};
        }
    } else {
        throw EtlUserException{""+field+" ("+time.toStdString()+"): Invalid time length - it must be: "+FORMAT_STR_TIME};
    }
}

unsigned DatasetInstance::whenToSeconds(QString when, string field)
{
    // 00:00:00
    if(when.length()==8) {
        if(when.at(2) == ':' && when.at(5) == ':') {
            QStringList hourSplit = when.split(':');
            if(hourSplit.length() == 3) {
                unsigned hours = hourSplit[0].toUInt();
                unsigned mins = hourSplit[1].toUInt();
                unsigned seconds = hourSplit[2].toUInt();
                return hours*3600+mins*60+seconds;
            } else {
                throw EtlUserException{""+field+" ("+when.toStdString()+"): Invalid hour format - it must be: "+FORMAT_STR_TIME};
            }
        } else {
            throw EtlUserException{""+field+" ("+when.toStdString()+"): Invalid time format - it must be: "+FORMAT_STR_TIME};
        }
    } else {
        throw EtlUserException{""+field+" ("+when.toStdString()+"): Invalid time length - it must be: "+FORMAT_STR_TIME};
    }
}

unsigned DatasetInstance::strMetersToMeters(QString strMeters, const string& field)
{
    // 28.000m
    if(strMeters.length()>=2 && strMeters.at(strMeters.length()-1) == 'm') {
        strMeters.replace(".", "");
        strMeters.chop(1);
        return strMeters.toUInt();
    } else {
        throw EtlUserException{""+field+": Invalid meters format - it must be like: 10.000m (was "+strMeters.toStdString()+")"};
    }
}

float DatasetInstance::strKgToKg(QString strKg, const string& field)
{
    // 91.2kg
    if(strKg.length()>2
            && strKg.at(strKg.length()-2) == 'k'
            && strKg.at(strKg.length()-1) == 'g')
    {
        strKg.chop(2);
        return strKg.toFloat();
    } else {
        throw EtlUserException{""+field+": Invalid kilograms format - it must be like: 91.9kg"};
    }
}

unsigned DatasetInstance::strGToG(QString strG, const string& field)
{
    // 23g
    if(strG.length()>=2 && strG.at(strG.length()-1) == 'g') {
        strG.chop(1);
        return strG.toUInt();
    } else {
        throw EtlUserException{""+field+": Invalid grams format - it must be like: 129g"};
    }
}

/*
 * methods
 */

DatasetInstance::DatasetInstance(
        unsigned year,
        unsigned month,
        unsigned day,
        QString when,
        unsigned phase,
        CategoricalValue activity,
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
        QString url,
        unsigned kcal,
        unsigned coolDownTimeSeconds,
        unsigned coolDownDistanceMeters,
        float weight,
        CategoricalValue weather,
        unsigned weatherTemperature,
        QString where,
        float bmi,
        unsigned gramsOfFatBurn,
        CategoricalValue source
):
    year(year),
    month(month),
    day(day),
    when(when),
    phase(phase),
    activity(activity),
    description(description),
    commute(commute),
    totalTimeSeconds(totalTimeSeconds),
    totalDistanceMeters(totalDistanceMeters),
    warmUpTimeSeconds(warmUpTimeSeconds),
    warmUpDistanceMeters(warmUpDistanceMeters),
    timeSeconds(timeSeconds),
    distanceMeters(distanceMeters),
    intensity(intensity),
    squats(squats),
    pushUps(pushUps),
    crunches(crunches),
    turtles(turtles),
    calfs(calfs),
    repetitions(repetitions),
    avgSpeed(avgSpeed),
    maxSpeed(maxSpeed),
    elevationGain(elevationGain),
    avgWatts(avgWatts),
    maxWatts(maxWatts),
    gear(gear),
    route(route),
    url(url),
    kcal(kcal),
    coolDownTimeSeconds(coolDownTimeSeconds),
    coolDownDistanceMeters(coolDownDistanceMeters),
    weight(weight),
    weather(weather),
    weatherTemperature(weatherTemperature),
    where(where),
    bmi(bmi),
    gramsOfFatBurnt(gramsOfFatBurn),
    source(source)
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
    << "  When: " << when.toStdString() << endl
    << "  Phase: " << phase << endl
    << "  Activity: " << activity.toString().toStdString() << endl
    << "  Description: " << description.toStdString() << endl
    << "  Commute: " << commute << endl
    << "  Total time: " << totalTimeSeconds << endl
    << "  Total meters: " << totalDistanceMeters << endl
    << "  Warm time: " << warmUpTimeSeconds << endl
    << "  Warm meters: " << warmUpDistanceMeters << endl
    << "  Time: " << timeSeconds << endl
    << "  Meters: " << distanceMeters << endl
    << "  Intensity: " << intensity.toString().toStdString() << endl
    << "  Squats: " << squats << endl
    << "  Push ups: " << pushUps << endl
    << "  Crunches: " << crunches << endl
    << "  Turtles: " << turtles << endl
    << "  Calfs: " << calfs << endl
    << "  Repetitions: " << repetitions << endl
    << "  Avg speed: " << avgSpeed << endl
    << "  Max speed: " << maxSpeed << endl
    << "  Elevation gain: " << elevationGain << endl
    << "  Avg watts: " << avgWatts << endl
    << "  Max watts: " << maxWatts << endl
    << "  Gear: " << gear.toString().toStdString() << endl
    << "  Route: " << route.toString().toStdString() << endl
    << "  URL: " << url.toStdString() << endl
    << "  kcal: " << kcal << endl
    << "  Cool time: " << coolDownTimeSeconds << endl
    << "  Cool meters: " << coolDownDistanceMeters << endl
    << "  Weight: " << weight << endl
    << "  Weather: " << weather.toString().toStdString() << endl
    << "  Temperature: " << weatherTemperature << endl
    << "  Where: " << where.toStdString() << endl
    << "  BMI: " << bmi << endl
    << "  Fat: " << gramsOfFatBurnt << endl
    << "  Source: " << source.toString().toStdString() << endl;


    return os.str();
}

string quoteCsvString(const string& s)
{
    string quoted{s}, quote{"\""};
    if(s.length()) {
        if(s[0] != quote[0]) {
            size_t found = quoted.find(',');
            if (found != string::npos) {
                quoted.insert(0, quote);
                quoted.append(quote);
            }
        }
    }
    return quoted;
}

string DatasetInstance::toCsv()
{
    stringstream os{};
    os
    << year << ", "
    << month << ", "
    << day << ", "
    << quoteCsvString(when.toStdString()) << ", "
    << phase << ", "
    << quoteCsvString(activity.toString().toStdString()) << ", "
    << quoteCsvString(description.toStdString()) << ", "
    << commute << ", "
    << totalTimeSeconds << ", "
    << totalDistanceMeters << ", "
    << warmUpTimeSeconds << ", "
    << warmUpDistanceMeters << ", "
    << timeSeconds << ", "
    << distanceMeters << ", "
    << quoteCsvString(intensity.toString().toStdString()) << ", "
    << squats << ", "
    << pushUps << ", "
    << crunches << ", "
    << turtles << ", "
    << calfs << ", "
    << repetitions << ", "
    << avgSpeed << ", "
    << maxSpeed << ", "
    << elevationGain << ", "
    << avgWatts << ", "
    << maxWatts << ", "
    << quoteCsvString(gear.toString().toStdString()) << ", "
    << quoteCsvString(route.toString().toStdString()) << ", "
    << quoteCsvString(url.toStdString()) << ", "
    << kcal << ", "
    << coolDownTimeSeconds << ", "
    << coolDownDistanceMeters << ", "
    << weight << ", "
    << quoteCsvString(weather.toString().toStdString()) << ", "
    << weatherTemperature << ", "
    << quoteCsvString(where.toStdString()) << ", "
    << bmi << ", "
    << gramsOfFatBurnt << ", "
    << quoteCsvString(source.toString().toStdString()) << endl;

    return os.str();
}

} // etl76 namespace
