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
#ifndef ETL76_DATASET_H
#define ETL76_DATASET_H

#include <vector>

#include "./dataset_instance.h"

namespace etl76 {

class Dataset
{
private:
    std::vector<DatasetInstance*> dataset;

public:
    Dataset();
    Dataset(const Dataset&) = delete;
    Dataset(const Dataset&&) = delete;
    Dataset&operator=(const Dataset&) = delete;
    Dataset&operator=(const Dataset&&) = delete;
    ~Dataset();

    void addInstance(DatasetInstance* instance) {
        dataset.push_back(instance);
    }

    std::vector<DatasetInstance*>& getInstances() { return dataset; }
};

}

#endif // ETL76_DATASET_H

