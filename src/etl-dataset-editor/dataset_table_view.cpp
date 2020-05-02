/*
 dataset_table_view.cpp     Endurance Training Log dataset editor

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
#include "dataset_table_view.h"

namespace etl76 {

using namespace std;

DatasetTableView::DatasetTableView(QWidget* parent)
  : QTableView(parent)
{
    verticalHeader()->setVisible(false);

    // BEFARE ::ResizeToContents this kills performance - use ::Fixed instead:
    // verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    setSortingEnabled(true);

    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void DatasetTableView::keyPressEvent(QKeyEvent* event)
{
    if(!(event->modifiers() & Qt::AltModifier)
         &&
       !(event->modifiers() & Qt::ControlModifier)
         &&
       !(event->modifiers() & Qt::ShiftModifier))
    {
        switch(event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Right:
            emit signalShowSelectedOutline();
            return;
        case Qt::Key_Down:
            QTableView::keyPressEvent(event);
            return;
        case Qt::Key_Up:
        // IMPROVE left to cancel selection
        case Qt::Key_Left:
            QTableView::keyPressEvent(event);
            return;
        }

        return;
    }

    QTableView::keyPressEvent(event);
}

void DatasetTableView::mouseDoubleClickEvent(QMouseEvent* event)
{
    Q_UNUSED(event);

    // double click to O opens it
    emit signalShowSelectedOutline();
}

void DatasetTableView::resizeEvent(QResizeEvent* event)
{
    cout << "OutlinesTableView::resizeEvent " << event << std::endl;

    // y/m/d
    if(horizontalHeader()->length() > 0) {
        // ensure that 1st column gets the remaining space from others
        horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    }
    verticalHeader()->setDefaultSectionSize(fontMetrics().height()*1.5);
    // importance/urgency
    this->setColumnWidth(1, this->fontMetrics().averageCharWidth()*12);
    this->setColumnWidth(2, this->fontMetrics().averageCharWidth()*12);
    // progress
    this->setColumnWidth(3, this->fontMetrics().averageCharWidth()*6);
    // notes
    this->setColumnWidth(4, this->fontMetrics().averageCharWidth()*5);
    // rd/wr
    this->setColumnWidth(5, this->fontMetrics().averageCharWidth()*5);
    this->setColumnWidth(6, this->fontMetrics().averageCharWidth()*5);
    // pretty
    this->setColumnWidth(7, this->fontMetrics().averageCharWidth()*12);

    QTableView::resizeEvent(event);
}

} // etl76 namespace
