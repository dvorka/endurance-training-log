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

using namespace std;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    // TODO app
    setWindowTitle(QString{"Endurance Training Log Dataset Editor"});

    // production dataset
    //datasetPath.assign("/home/dvorka/p/endurance-training-log/github/endurance-training-log/datasets/training-log-days.csv");
    // test dataset
    datasetPath.assign("/home/dvorka/p/endurance-training-log/github/endurance-training-log/test/datasets/training-log-days.csv");

    // menu
    QMenu* fileMenu = menuBar()->addMenu("&File");
    QAction* openCsvAction = fileMenu->addAction("&Open");
    QAction* saveCsvAction = fileMenu->addAction("&Save");
    QAction* saveAsCsvAction = fileMenu->addAction("Save &as");
    QAction* quitAction = fileMenu->addAction("&Quit");
    QMenu* datasetMenu = menuBar()->addMenu("&Dataset");
    QAction* newInstanceAction = datasetMenu->addAction("&New instance");

    // window
    datasetTableView = new DatasetTableView{this};
    datasetTablePresenter = new DatasetTablePresenter{datasetTableView};
    datasetTablePresenter->getModel()->setRows(&dataset);

    setCentralWidget(datasetTableView);
    statusBar()->clearMessage();
    setWindowState(Qt::WindowMaximized);

    // dialogs
    newInstanceDialog = new DatasetInstanceDialog{this};
    checkInstanceDialog = new DatasetInstanceCheckDialog{this};

    // signals
    QObject::connect(
        datasetTableView, SIGNAL(signalShowSelectedInstance()),
        this, SLOT(slotShowSelectedInstanceInDialog())
    );
    QObject::connect(
        newInstanceAction, SIGNAL(triggered()),
        this, SLOT(slotNewInstanceDialog())
    );
    QObject::connect(
        newInstanceDialog, SIGNAL(accepted()),
        this, SLOT(slotHandleNewInstance())
    );
    QObject::connect(
        quitAction, SIGNAL(triggered()),
        this, SLOT(close())
    );
}

MainWindow::~MainWindow()
{
    delete datasetTableView;
    delete datasetTablePresenter;
}

void MainWindow::onStart()
{
    if(Dataset::file_exists(datasetPath)) {
        dataset.from_csv(datasetPath);
    }
    datasetTablePresenter->getModel()->setRows(&dataset);
}

void MainWindow::slotNewInstanceDialog() {
    newInstanceDialog->refreshOnNew();
    newInstanceDialog->show();
}

void MainWindow::slotShowSelectedInstanceInDialog()
{
    int row = datasetTablePresenter->getCurrentRow();

    cout << "Show selected instance: " << row << endl;

    if(row != DatasetTablePresenter::NO_ROW) {
        QStandardItem* item = datasetTablePresenter->getModel()->item(row);
        if(item) {
            DatasetInstance* instance = item->data(Qt::UserRole + 1).value<DatasetInstance*>();
            newInstanceDialog->fromInstance(instance);
            newInstanceDialog->show();
            return;
        } else {
            statusBar()->showMessage(QString(tr("Error: selected dataset instance not found in the model")));
        }
    }
}

void MainWindow::slotHandleNewInstance()
{
    DatasetInstance* newInstance = newInstanceDialog->toDatasetInstance();
    checkInstanceDialog->refreshOnCheck(newInstance->toString());
    checkInstanceDialog->show();

    dataset.addInstance(newInstance);
    datasetTablePresenter->getModel()->setRows(&dataset);

    dataset.to_csv(datasetPath);
}

void MainWindow::addFooDatasetRow()
{
    dataset.addInstance(
        new DatasetInstance(
        2020, 05, 02,
        1,
        CategoricalValue{QString{"bike"}},
        QString("Easy in windy weather"),
        false,
        3600, 25000,
        0, 0, 0, 0,
        CategoricalValue{QString{"easy"}},
        0, 0, 0,
        CategoricalValue{QString{"Rockhopper"}},
        CategoricalValue{QString{}},
        QString(""),
        0, 0, 0,
        92.5,
        CategoricalValue{QString{"sunny"}}, 15,
        QString("TV"),
        0
        )
    );
}

} // namespace etl76
