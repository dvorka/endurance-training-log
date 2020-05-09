# etl-dataset-editor.pro     Endurance Training Log dataset editor
#
# Copyright (C) 2020 Martin Dvorak <martin.dvorak@mindforger.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dataset.cpp \
    dataset_instance.cpp \
    dataset_instance_check_dialog.cpp \
    dataset_table_model.cpp \
    dataset_table_presenter.cpp \
    dataset_table_view.cpp \
    etl_dataset_editor.cpp \
    main_window.cpp \
    statistics.cpp \
    dataset_instance_dialog.cpp

HEADERS += \
    csv.h \
    dataset.h \
    dataset_instance.h \
    dataset_instance_check_dialog.h \
    dataset_table_model.h \
    dataset_table_presenter.h \
    dataset_table_view.h \
    exceptions.h \
    main_window.h \
    statistics.h \
    dataset_instance_dialog.h

TRANSLATIONS += \
    etl-dataset-editor_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
