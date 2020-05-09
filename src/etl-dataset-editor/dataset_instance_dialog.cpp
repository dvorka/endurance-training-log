/*
 dataset_instance_dialog.cpp     Endurance Training Log dataset editor

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
#include "dataset_instance_dialog.h"

namespace etl76 {

DatasetInstanceDialog::DatasetInstanceDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("New Instance");

    yearMonthDayLabel = new QLabel{"Year/month/day:", this};
    yearMonthDayEdit = new QLineEdit{this};

    activityLabel = new QLabel{"Activity:", this};
    activityEdit = new QLineEdit{this};

    descriptionLabel = new QLabel{"Description:", this};
    descriptionEdit = new QLineEdit{this};

    phaseLabel = new QLabel{"Phase:", this};
    // spinner
    phaseEdit = new QLineEdit{this};

    commuteLabel = new QLabel{"Commute:", this};
    commuteCheck = new QCheckBox{this};

    totalTimeLabel = new QLabel{"Total time:", this};
    totalTimeEdit = new QLineEdit{this};
    totalTimeEdit->setDisabled(true);
    totalTimeEdit->setToolTip("hh:mm.ss");
    totalDistanceLabel = new QLabel{"Total distance:", this};
    totalDistanceLabel->setToolTip("meters");
    totalDistanceEdit = new QLineEdit{this};
    totalDistanceEdit->setDisabled(true);

    warmUpTimeLabel = new QLabel{"Warm-up time:", this};
    warmUpTimeEdit = new QLineEdit{this};
    warmUpTimeEdit->setToolTip("hh:mm.ss");
    warmUpDistanceLabel = new QLabel{"Warm-up distance:", this};
    warmUpDistanceEdit = new QLineEdit{this};
    warmUpDistanceEdit->setToolTip("meters");

    timeLabel = new QLabel{"Time:", this};
    timeEdit = new QLineEdit{this};
    timeEdit->setToolTip("hh:mm.ss");
    distanceLabel = new QLabel{"Distance:", this};
    distanceEdit = new QLineEdit{this};
    distanceEdit->setToolTip("meters");

    intensityLabel = new QLabel{"Intensity:", this};
    intensityEdit = new QLineEdit{this};
    repetitionsLabel = new QLabel{"Repetitions:", this};
    // spinner w/ present
    repetitionsEdit = new QLineEdit{this};
    avgWattsLabel = new QLabel{"Avg watts:", this};
    // spinner w/ present
    avgWattsEdit = new QLineEdit{this};
    maxWattsLabel = new QLabel{"Max watts:", this};
    // spinner w/ present
    maxWattsEdit = new QLineEdit{this};

    equipmentLabel = new QLabel{"Equipment:", this};
    // dropdown
    equipmentEdit = new QLineEdit{this};
    routeLabel = new QLabel{"Route:", this};
    routeEdit = new QLineEdit{this};
    gpxUrlLabel = new QLabel{"GPX URL:", this};
    gpxUrlEdit = new QLineEdit{this};

    caloriesLabel = new QLabel{"Calories:", this};
    // spinner w/ preset (typically calculated)
    caloriesEdit = new QLineEdit{this};

    coolDownTimeLabel = new QLabel{"Cool-down time:", this};
    coolDownTimeEdit = new QLineEdit{this};
    coolDownTimeEdit->setToolTip("hh:mm.ss");
    coolDownDistanceLabel = new QLabel{"Cool-down distance:", this};
    coolDownDistanceEdit = new QLineEdit{this};
    coolDownDistanceEdit->setToolTip("meters");

    weightLabel = new QLabel{"Weight:", this};
    weightEdit = new QLineEdit{this};
    weightEdit->setToolTip("00.0kg");

    weatherLabel = new QLabel{"Weather:", this};
    // dropdown
    weatherEdit = new QLineEdit{this};
    weatherTemperatureLabel = new QLabel{"Temperature °C:", this};
    weatherTemperatureEdit = new QLineEdit{this};
    weatherTemperatureEdit->setToolTip("celsius");

    whereLabel = new QLabel{"Where:", this};
    // dropdown
    whereEdit = new QLineEdit{this};

    gramsOfFatBurntLabel = new QLabel{"Burnt fat:", this};
    // spinner w/ present
    gramsOfFatBurntEdit = new QLineEdit{this};
    gramsOfFatBurntEdit->setDisabled(true);

    QHBoxLayout* columnsLayout = new QHBoxLayout{this};
    QVBoxLayout* leftLayout = new QVBoxLayout{this};
    QVBoxLayout* rightLayout = new QVBoxLayout{this};
    columnsLayout->addLayout(leftLayout);
    columnsLayout->addLayout(rightLayout);

    leftLayout->addWidget(yearMonthDayLabel);
    leftLayout->addWidget(yearMonthDayEdit);

    leftLayout->addWidget(activityLabel);
    leftLayout->addWidget(activityEdit);

    leftLayout->addWidget(descriptionLabel);
    leftLayout->addWidget(descriptionEdit);

    leftLayout->addWidget(phaseLabel);
    leftLayout->addWidget(phaseEdit);

    leftLayout->addWidget(commuteLabel);
    leftLayout->addWidget(commuteCheck);

    leftLayout->addWidget(totalTimeLabel);
    leftLayout->addWidget(totalTimeEdit);
    leftLayout->addWidget(totalDistanceLabel);
    leftLayout->addWidget(totalDistanceEdit);

    leftLayout->addWidget(warmUpTimeLabel);
    leftLayout->addWidget(warmUpTimeEdit);
    leftLayout->addWidget(warmUpDistanceLabel);
    leftLayout->addWidget(warmUpDistanceEdit);

    leftLayout->addWidget(timeLabel);
    leftLayout->addWidget(timeEdit);
    leftLayout->addWidget(distanceLabel);
    leftLayout->addWidget(distanceEdit);

    leftLayout->addWidget(intensityLabel);
    leftLayout->addWidget(intensityEdit);
    leftLayout->addWidget(repetitionsLabel);
    leftLayout->addWidget(repetitionsEdit);
    leftLayout->addWidget(avgWattsLabel);
    leftLayout->addWidget(avgWattsEdit);
    rightLayout->addWidget(maxWattsLabel);
    rightLayout->addWidget(maxWattsEdit);

    rightLayout->addWidget(equipmentLabel);
    rightLayout->addWidget(equipmentEdit);
    rightLayout->addWidget(routeLabel);
    rightLayout->addWidget(routeEdit);
    rightLayout->addWidget(gpxUrlLabel);
    rightLayout->addWidget(gpxUrlEdit);

    rightLayout->addWidget(caloriesLabel);
    rightLayout->addWidget(caloriesEdit);

    rightLayout->addWidget(coolDownTimeLabel);
    rightLayout->addWidget(coolDownTimeEdit);
    rightLayout->addWidget(coolDownDistanceLabel);
    rightLayout->addWidget(coolDownDistanceEdit);

    rightLayout->addWidget(weightLabel);
    rightLayout->addWidget(weightEdit);

    rightLayout->addWidget(weatherLabel);
    rightLayout->addWidget(weatherEdit);
    rightLayout->addWidget(weatherTemperatureLabel);
    rightLayout->addWidget(weatherTemperatureEdit);

    rightLayout->addWidget(whereLabel);
    rightLayout->addWidget(whereEdit);

    rightLayout->addWidget(gramsOfFatBurntLabel);
    rightLayout->addWidget(gramsOfFatBurntEdit);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    rightLayout->addWidget(buttonBox);

    // signals
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    resize(fontMetrics().averageCharWidth()*90, height());
    setLayout(columnsLayout);
    setModal(true);
}

void DatasetInstanceDialog::clearAllItems()
{
    // TODO set current
    yearMonthDayEdit->setText("2020/05/03");
    descriptionEdit->clear();
    phaseEdit->setText("1");
    activityEdit->setText("ride");
    commuteCheck->setChecked(false);
    totalTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    totalDistanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    warmUpTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    warmUpDistanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    timeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    distanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    intensityEdit->setText("easy");
    repetitionsEdit->setText("0");
    avgWattsEdit->setText("0");
    maxWattsEdit->setText("0");
    equipmentEdit->clear();
    routeEdit->clear();
    gpxUrlEdit->clear();
    caloriesEdit->setText("0");
    coolDownTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    coolDownDistanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    weightEdit->setText(DatasetInstance::DEFAULT_STR_WEIGHT);
    weatherEdit->setText("sunny");
    weatherTemperatureEdit->setText("0");
    whereEdit->setText("TV");
    gramsOfFatBurntEdit->setText(DatasetInstance::DEFAULT_STR_GRAMS);
}

void DatasetInstanceDialog::fromInstance(DatasetInstance* instance)
{
    yearMonthDayEdit->setText(instance->getYearMonthDay());
    phaseEdit->setText(QString::number(instance->getPhase()));
    activityEdit->setText(instance->getActivityType().toString());
    descriptionEdit->setText(instance->getDescription());
    commuteCheck->setChecked(false);
    totalTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    totalDistanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    warmUpTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    warmUpDistanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    timeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    distanceEdit->setText(DatasetInstance::DEFAULT_STR_METERS);
    intensityEdit->setText("easy");
    repetitionsEdit->setText("0");
    avgWattsEdit->setText(QString::number(instance->getAvgWatts()));
    maxWattsEdit->setText(QString::number(instance->getMaxWatts()));
    equipmentEdit->setText(instance->getEquipment().toString());
    routeEdit->setText(instance->getRoute().toString());
    gpxUrlEdit->setText(instance->getGpxUrl());
    caloriesEdit->setText(QString::number(instance->getCalories()));
    coolDownTimeEdit->setText(DatasetInstance::DEFAULT_STR_TIME);
    coolDownDistanceEdit->setText(QString::number(instance->getCoolDownDistanceMeters()).append("m"));
    weightEdit->setText(DatasetInstance::DEFAULT_STR_WEIGHT);
    weatherEdit->clear();
    weatherTemperatureEdit->setText(QString::number(instance->getWeatherTemperature()));
    whereEdit->setText(instance->getWhere());
    gramsOfFatBurntEdit->setText(QString::number(instance->getGramsOfFatBurnt()).append("g"));
}

DatasetInstance* DatasetInstanceDialog::toDatasetInstance()
{
    DatasetInstance* instance = new DatasetInstance{
        DatasetInstance::ymdToYear(yearMonthDayEdit->text()),
        DatasetInstance::ymdToMonth(yearMonthDayEdit->text()),
        DatasetInstance::ymdToDay(yearMonthDayEdit->text()),
        phaseEdit->text().toUInt(),
        CategoricalValue(activityEdit->text()),
        descriptionEdit->text(),
        commuteCheck->isChecked(),
        DatasetInstance::strTimeToSeconds(totalTimeEdit->text()),
        DatasetInstance::strMetersToMeters(totalDistanceEdit->text()),
        DatasetInstance::strTimeToSeconds(warmUpTimeEdit->text()),
        DatasetInstance::strMetersToMeters(warmUpDistanceEdit->text()),
        DatasetInstance::strTimeToSeconds(timeEdit->text()),
        DatasetInstance::strMetersToMeters(distanceEdit->text()),
        CategoricalValue(intensityEdit->text()),
        repetitionsEdit->text().toUInt(),
        avgWattsEdit->text().toUInt(),
        maxWattsEdit->text().toUInt(),
        CategoricalValue(equipmentEdit->text()),
        CategoricalValue(routeEdit->text()),
        QString(gpxUrlEdit->text()),
        caloriesEdit->text().toUInt(),
        DatasetInstance::strTimeToSeconds(coolDownTimeEdit->text()),
        DatasetInstance::strMetersToMeters(coolDownDistanceEdit->text()),
        weightEdit->text().toFloat(),
        CategoricalValue(weatherEdit->text()),
        weatherTemperatureEdit->text().toUInt(),
        whereEdit->text(),
        gramsOfFatBurntEdit->text().toUInt()
    };

    // TODO show.toString() and let user confirm that it's OK (just text area)

    // TODO
    // instance->validate();
    // instance->calculate(); // calories, grams of fat, BMI, total time, either time/distance/both, ...

    return instance;
}

// TODO validate
// TODO recalculation rules on particular fields editation

} // etl76 namespace
