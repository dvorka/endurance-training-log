/*
 main_window.cpp     Endurance Training Log dataset editor

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
#include "main_window.h"

namespace etl76 {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // TODO app
    setWindowTitle(QString{"Endurance Training Log Dataset Editor"});
    QMenu* fileMenu = menuBar()->addMenu("&File");
    QAction* openCsvAction = fileMenu->addAction("&Open");
    QAction* saveCsvAction = fileMenu->addAction("&Save");
    QAction* saveAsCsvAction = fileMenu->addAction("Save &as");
    QAction* quitAction = fileMenu->addAction("&Quit");
    QMenu* datasetMenu = menuBar()->addMenu("&Dataset");
    QAction* newInstanceAction = datasetMenu->addAction("&New instance");

    newInstanceDialog = new DatasetInstanceDialog{this};

    statusBar()->clearMessage();
    setWindowState(Qt::WindowMaximized);

    dataset.addInstance(
        new DatasetInstance(
        2020, 05, 02,
        1,
        CategoricalValue("bike"),
        QString("Easy Okor in windy weather"),
        false,
        3600, 25000,
        0, 0, 0, 0,
        CategoricalValue("easy"),
        0, 0, 0,
        CategoricalValue("Rockhopper"),
        CategoricalValue(""),
        QString(""),
        0, 0, 0,
        92.5,
        CategoricalValue("sunny"), 15,
        QString("Skupice"),
        0
        )
    );

    datasetTableView = new DatasetTableView{this};
    datasetTablePresenter = new DatasetTablePresenter{datasetTableView};
    datasetTablePresenter->getModel()->setRows(&dataset);

    // TODO expendable splitter
    QSplitter* splitter = new QSplitter;
    splitter->addWidget(datasetTableView);

    setCentralWidget(datasetTableView);

    // signals
    QObject::connect(
        newInstanceDialog, SIGNAL(accepted()),
        this, SLOT(handleNewInstance())
    );
    QObject::connect(
        quitAction, SIGNAL(triggered()),
        this, SLOT(close())
    );
    QObject::connect(
        newInstanceAction, SIGNAL(triggered()),
        this, SLOT(showNewInstanceDialog())
    );
}

MainWindow::~MainWindow()
{
    delete datasetTableView;
    delete datasetTablePresenter;
}

void MainWindow::handleNewInstance()
{
    DatasetInstance* newInstance = newInstanceDialog->toDatasetInstance();
    dataset.addInstance(newInstance);
    datasetTablePresenter->getModel()->setRows(&dataset);
}

} // namespace etl76
