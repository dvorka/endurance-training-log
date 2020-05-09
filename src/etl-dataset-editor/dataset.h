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

#include <fstream>
#include <stdio.h>
#include <sys/stat.h>
#include <vector>

#include "csv.h"
#include "dataset_instance.h"
#include "exceptions.h"

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

    void clear();

    void addInstance(DatasetInstance* instance) {
        dataset.push_back(instance);
    }
    void insertInstance(DatasetInstance* instance) {
        dataset.insert(dataset.begin()+instance->getDatasetIndex(), instance);
    }
    void setInstance(int index, DatasetInstance* instance) {
        removeInstance(index);
        dataset[index]=instance;
    }

    int removeInstance(int index);
    void switchInstances(int a, int b);
    int upInstance(int index);
    int downInstance(int index);

    std::vector<DatasetInstance*>& getInstances() { return dataset; }

    void from_csv(const std::string& file_path);
    void to_csv(const std::string& file_path) const;

    static bool file_exists(const std::string& file_path);
};

} // namespace etl76

#endif // ETL76_DATASET_H
