/*
 main_window.h     Endurance Training Log dataset editor

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
#ifndef ETL76_MAIN_WINDOW_H
#define ETL76_MAINWINDOW_H

#include <QMainWindow>

#include "dataset.h"
#include "dataset_table_view.h"
#include "dataset_table_model.h"
#include "dataset_table_presenter.h"

namespace etl76 {

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Dataset dataset;

    DatasetTableView* view;
    DatasetTableModel* model;
    DatasetTablePresenter* presenter;

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

}

#endif // MAIN_WINDOW_H
