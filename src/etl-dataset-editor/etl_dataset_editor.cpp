/*
 etl_dataset_editor.cpp     Endurance Training Log dataset editor

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

#include <QApplication>


/**
 * @brief Endurance Training Log CLI.
 */
int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName(QString{"Endurance Training Log Dataset Editor"});
    etl76::MainWindow mainWindow;
    mainWindow.show();
    return application.exec();
}
