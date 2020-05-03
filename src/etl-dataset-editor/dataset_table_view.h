/*
 dataset_table_view.h     Endurance Training Log dataset editor

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
#ifndef ETL76_OUTLINES_TABLE_H_
#define ETL76_OUTLINES_TABLE_H_

#include <iostream>
#include <vector>

#include <QtWidgets>

namespace etl76 {

class DatasetTableView : public QTableView
{
    Q_OBJECT

private:
    // if view is width < threshold columns, then shows simplified view w/o Mind-related columns
    static constexpr int SIMPLIFIED_VIEW_THRESHOLD_WIDTH = 75*2;

public:
    static const int COLUMN_COUNT = 7;
public:
    explicit DatasetTableView(QWidget* parent);
    DatasetTableView(const DatasetTableView&) = delete;
    DatasetTableView(const DatasetTableView&&) = delete;
    DatasetTableView &operator=(const DatasetTableView&) = delete;
    DatasetTableView &operator=(const DatasetTableView&&) = delete;
    virtual ~DatasetTableView() override {}

    int getColumnCount() { return COLUMN_COUNT; }

    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void resizeEvent(QResizeEvent* event) override;

signals:
    void signalShowSelectedOutline();
    void signalFindOutlineByName();
};

}

#endif // ETL76_OUTLINES_TABLE_H_
