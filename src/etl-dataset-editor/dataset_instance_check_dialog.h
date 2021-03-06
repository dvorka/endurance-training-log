/*
 dataset_instance_check_dialog.h     Endurance Training Log dataset editor

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
#ifndef ETL76_DATASET_INSTANCE_CHECK_DIALOG_H
#define ETL76_DATASET_INSTANCE_CHECK_DIALOG_H

#include <QtWidgets>

#include "dataset_instance.h"


namespace etl76 {

class DatasetInstanceCheckDialog : public QDialog
{
    Q_OBJECT

public:
    // widgets to avoid wrong inputs: number spinners, drop-downs, ...

    QLabel* checkLabel;
    QPlainTextEdit* checkTextEdit;

    QDialogButtonBox* buttonBox;

public:
    explicit DatasetInstanceCheckDialog(QWidget* parent = 0);

    void refreshOnCheck(std::string checkText) {
        checkTextEdit->insertPlainText(QString::fromStdString(checkText));
    };
};

} // namespace etl76

#endif // DATASET_INSTANCE_DIALOG_H
