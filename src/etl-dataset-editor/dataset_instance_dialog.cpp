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
    QVBoxLayout* mainLayout = new QVBoxLayout{this};
    yearLabel = new QLabel{"Year:", this};
    yearEdit = new QLineEdit{this};
    monthLabel = new QLabel{"Month:", this};
    monthEdit = new QLineEdit{this};
    dayLabel = new QLabel{"Day:", this};
    dayEdit = new QLineEdit{this};

    phaseLabel = new QLabel{"Phase:", this};
    // spinner
    phaseEdit = new QLineEdit{this};

    commuteLabel = new QLabel{"Commute:", this};
    commuteCheck = new QCheckBox{this};


    mainLayout->addWidget(yearLabel);
    mainLayout->addWidget(yearEdit);
    mainLayout->addWidget(monthLabel);
    mainLayout->addWidget(monthEdit);
    mainLayout->addWidget(dayLabel);
    mainLayout->addWidget(dayEdit);

    mainLayout->addWidget(phaseLabel);
    mainLayout->addWidget(phaseEdit);

    mainLayout->addWidget(commuteLabel);
    mainLayout->addWidget(commuteCheck);

    resize(fontMetrics().averageCharWidth()*60, height());
    setLayout(mainLayout);
    setModal(true);
}

} // etl76 namespace
