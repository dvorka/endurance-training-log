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
    // QAction* openCsvAction = fileMenu->addAction("&Open");
    // QAction* saveCsvAction = fileMenu->addAction("&Save");
    // QAction* saveAsCsvAction = fileMenu->addAction("Save &as");
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
    editInstanceDialog = new DatasetInstanceDialog{this};

    // signals
    QObject::connect(
        datasetTableView, SIGNAL(signalShowSelectedInstance()),
        this, SLOT(slotEditSelectedInstanceInDialog())
    );
    QObject::connect(
        newInstanceAction, SIGNAL(triggered()),
        this, SLOT(slotNewInstanceDialog())
    );
    QObject::connect(
        editInstanceDialog, SIGNAL(accepted()),
        this, SLOT(slotHandleEditInstance())
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
        try {
            dataset.from_csv(datasetPath);
        } catch(io::error::missing_column_in_header e) {
            QMessageBox::critical(
                this,
                tr("CSV Dataset Load Error"),
                e.what(),
                QMessageBox::Ok
            );
        }
    }
    datasetTablePresenter->getModel()->setRows(&dataset);
}

void MainWindow::slotNewInstanceDialog() {
    editInstanceDialog->refreshOnCreate();
    editInstanceDialog->show();
}

void MainWindow::slotEditSelectedInstanceInDialog()
{
    int row = datasetTablePresenter->getCurrentRow();

    cout << "Edit selected instance: " << row << endl;

    if(row != DatasetTablePresenter::NO_ROW) {
        QStandardItem* item = datasetTablePresenter->getModel()->item(row);
        if(item) {
            DatasetInstance* instance = item->data(Qt::UserRole + 1).value<DatasetInstance*>();
            editInstanceDialog->refreshOnEdit(instance, row);
            editInstanceDialog->show();
            return;
        } else {
            QMessageBox::warning(
                this,
                tr("Error"),
                tr("Selected dataset instance was not found in the  dataset model"),
                QMessageBox::Ok
            );
        }
    }
}

void MainWindow::slotHandleEditInstance()
{
    try {
        DatasetInstance* instance = editInstanceDialog->toDatasetInstance();
        if(editInstanceDialog->isCreateMode()) {
            dataset.addInstance(instance);
        } else {
            dataset.setInstance(editInstanceDialog->getDatasetIndex(), instance);
        }
        datasetTablePresenter->getModel()->setRows(&dataset);
        dataset.to_csv(datasetPath);
    } catch(EtlUserException e) {
        QMessageBox::warning(
            this,
            tr("Dataset Instance Validation Error"),
            e.what(),
            QMessageBox::Ok
        );
        editInstanceDialog->show();
    }
}

} // namespace etl76
