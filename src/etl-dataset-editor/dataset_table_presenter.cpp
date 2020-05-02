/*
 dataset_table_presenter.cpp     Endurance Training Log dataset editor

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
#include "dataset_table_presenter.h"

using namespace std;

namespace etl76 {

DatasetTablePresenter::DatasetTablePresenter(DatasetTableView* view)
{
    this->view = view;
    this->model = new DatasetTableModel(this);
    this->view->setModel(this->model);
}

void DatasetTablePresenter::refresh(const vector<DatasetInstance*>& instances)
{
    model->removeAllRows();
    if(instances.size()) {
        for(DatasetInstance* instance:instances) {
            model->addRow(instance);
        }

        this->view->setCurrentIndex(this->model->index(0, 0));
        this->view->setFocus();
    }
}

int DatasetTablePresenter::getCurrentRow() const
{
    QModelIndexList indexes = view->selectionModel()->selection().indexes();
    for(int i=0; i<indexes.count(); i++) {
        return indexes.at(i).row();
    }
    return NO_ROW;
}

} // etl76 namespace
