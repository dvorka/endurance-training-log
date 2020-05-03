/*
 dataset_instance_dialog.h     Endurance Training Log dataset editor

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
#ifndef ETL76_DATASET_INSTANCE_DIALOG_H
#define ETL76_DATASET_INSTANCE_DIALOG_H

#include <QtWidgets>

#include "dataset_instance.h"


namespace etl76 {

class DatasetInstanceDialog : public QDialog
{
    Q_OBJECT

public:
    QLabel* yearMonthDayLabel;
    QLineEdit* yearMonthDayEdit;

    QLabel* activityLabel;
    QLineEdit* activityEdit;

    QLabel* descriptionLabel;
    QLineEdit* descriptionEdit;

    QLabel* phaseLabel;
    QLineEdit* phaseEdit;

    QLabel* commuteLabel;
    QCheckBox* commuteCheck;

    QLabel* totalTimeLabel;
    QLineEdit* totalTimeEdit;
    QLabel* totalDistanceLabel;
    QLineEdit* totalDistanceEdit;

    QLabel* warmUpTimeLabel;
    QLineEdit* warmUpTimeEdit;
    QLabel* warmUpDistanceLabel;
    QLineEdit* warmUpDistanceEdit;

    QLabel* timeLabel;
    QLineEdit* timeEdit;
    QLabel* distanceLabel;
    QLineEdit* distanceEdit;

    QLabel* intensityLabel;
    QLineEdit* intensityEdit;
    QLabel* repetitionsLabel;
    QLineEdit* repetitionsEdit;
    QLabel* avgWattsLabel;
    QLineEdit* avgWattsEdit;
    QLabel* maxWattsLabel;
    QLineEdit* maxWattsEdit;

    QLabel* equipmentLabel;
    QLineEdit* equipmentEdit;
    QLabel* routeLabel;
    QLineEdit* routeEdit;
    QLabel* gpxUrlLabel;
    QLineEdit* gpxUrlEdit;

    QLabel* caloriesLabel;
    QLineEdit* caloriesEdit;

    QLabel* coolDownTimeLabel;
    QLineEdit* coolDownTimeEdit;
    QLabel* coolDownDistanceLabel;
    QLineEdit* coolDownDistanceEdit;

    QLabel* weightLabel;
    QLineEdit* weightEdit;

    QLabel* weatherLabel;
    QLineEdit* weatherEdit;
    QLabel* weatherTemperatureLabel;
    QLineEdit* weatherTemperatureEdit;

    QLabel* whereLabel;
    QLineEdit* whereEdit;

    QLabel* gramsOfFatBurntLabel;
    QLineEdit* gramsOfFatBurntEdit;

    QDialogButtonBox* buttonBox;

public:
    explicit DatasetInstanceDialog(QWidget* parent = 0);

    void refreshOnNew() { clearAllItems(); }

    void fromInstance(DatasetInstance* instance);
    DatasetInstance* toDatasetInstance();

signals:

public slots:

private:
    void clearAllItems();

};

} // namespace etl76

#endif // DATASET_INSTANCE_DIALOG_H
