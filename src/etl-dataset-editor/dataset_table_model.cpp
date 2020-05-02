/*
 dataset_table_model.cpp     Endurance Training Log dataset editor

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
#include "dataset_table_model.h"

namespace etl76 {

using namespace std;

DatasetTableModel::DatasetTableModel(QObject* parent)
    : QStandardItemModel(parent)
{
    setColumnCount(5);
    setRowCount(0);
}

void DatasetTableModel::removeAllRows()
{
    QStandardItemModel::clear();

    QStringList tableHeader;
    tableHeader
        << tr("Date")       // 2020/05/21 (use modified:1)
        << tr("Phase")      // 1
        << tr("Activity")   // running    (use Notebook:8 ~ non-fixed width)
        << tr("Distance")   // 1,250m
        << tr("Time")       // 1h30m12s
        << tr("Intensity")  // fatlek
        << tr("Weight")     // 92.5kg
        << tr("Fat");       // 12g        (grams of fat burn)
    // IMPROVE set tooltips: items w/ tooltips instead of just strings
    setHorizontalHeaderLabels(tableHeader);
}

void DatasetTableModel::addRows(Dataset* dataset)
{
    for(DatasetInstance* instance: dataset->getInstances()) {
        addRow(instance);
    }
}

void DatasetTableModel::addRow(DatasetInstance* instance)
{
    QList<QStandardItem*> items;
    QStandardItem* item;

    cout << "Adding: " << instance->getYear() << endl;

    // year/month/day
    item = new QStandardItem(instance->getYearMonthDay());
    // sort
    item->setData(QVariant::fromValue((unsigned)(
        instance->getYear()*10000+
        instance->getMonth()*100+
        instance->getDay())),
        Qt::UserRole
    );
    items += item;

    // phase
    item = new QStandardItem(instance->getPhase());
    item->setData(QVariant::fromValue((unsigned)(instance->getPhase())), Qt::UserRole);
    items += item;

    // activity
    item = new QStandardItem(instance->getActivityType().toString());
    items += item;

    // distance
    item = new QStandardItem(instance->getDistanceStr());
    item->setData(QVariant::fromValue((unsigned)(instance->getDistanceMeters())), Qt::UserRole);
    items += item;

    // time
    item = new QStandardItem(instance->getTotalTimeStr());
    item->setData(QVariant::fromValue((unsigned)(instance->getTotalTimeSeconds())), Qt::UserRole);
    items += item;

    // intesity
    item = new QStandardItem(instance->getIntensity().toString());
    items += item;

    // weight
    item = new QStandardItem(instance->getWeightStr());
    item->setData(QVariant::fromValue((unsigned)(instance->getWeight())), Qt::UserRole);
    items += item;

    // fat
    item = new QStandardItem(instance->getGramsOfFatBurntStr());
    item->setData(QVariant::fromValue((unsigned)(instance->getGramsOfFatBurnt())), Qt::UserRole);
    items += item;

    appendRow(items);
}

} // etl76 namespace
