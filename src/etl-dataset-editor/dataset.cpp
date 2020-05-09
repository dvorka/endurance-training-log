/*
 dataset.h     Endurance Training Log dataset editor

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
#include "dataset.h"


namespace etl76 {

using namespace std;

Dataset::Dataset()
{
}

Dataset::~Dataset()
{
    clear();
}

void Dataset::clear()
{
    for(DatasetInstance* i:dataset) {
        delete i;
    }
}

void from_csv(const std::string file_path)
{
    io::CSVReader<3> in(file_path);
    in.read_header(
        io::ignore_extra_column,
        "vendor",
        "size",
        "speed"
    );
    std::string vendor; int size; double speed;
    while(in.read_row(vendor, size, speed)){
        // do stuff with the data
    }
}

} // etl76 namespace
