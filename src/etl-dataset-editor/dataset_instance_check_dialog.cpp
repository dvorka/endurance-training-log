/*
 dataset_instance_check_dialog.cpp     Endurance Training Log dataset editor

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
#include "dataset_instance_check_dialog.h"

namespace etl76 {

DatasetInstanceCheckDialog::DatasetInstanceCheckDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Validated and Parsed Dataset Instance Check");

    checkLabel = new QLabel{"Use 'OK' to save instance or 'Cancel' to go back to edit dialog:", this};
    checkTextEdit = new QPlainTextEdit(this);
    checkTextEdit->setDisabled(true);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    QVBoxLayout* centralLayout = new QVBoxLayout{this};
    centralLayout->addWidget(checkLabel);
    centralLayout->addWidget(checkTextEdit);
    centralLayout->addWidget(buttonBox);

    // signals
    QObject::connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    resize(fontMetrics().averageCharWidth()*70, height());
    setLayout(centralLayout);
    setModal(true);
}

} // etl76 namespace
