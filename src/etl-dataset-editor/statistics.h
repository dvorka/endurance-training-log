/*
 statistics.h     Endurance Training Log dataset editor

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
#ifndef ETL76_STATISTICS_H
#define ETL76_STATISTICS_H


namespace etl76 {

/**
 * @brief Statistics.
 *
 * Calculates and saves weekly, monthly and yearly statistics for given
 * (day by day) dataset (3 files).
 *
 * Weekly:
 * - total universal km
 * - total universal time
 * - cycling km
 * - C2 km
 * - running km
 * - total workout repetitions
 * - avg weight
 * - min weight
 * - max weight
 * - weight delta
 * - sauna rounds + meditations
 *
 * Monthly:
 * - ... same as weekly
 *
 * Yearly:
 * - ... same as weekly
 * - avg weekly km
 * - avg montly km
 *
 */
class Statistics
{
public:
    Statistics();
};

} // namespace etl76

#endif // ETL76_STATISTICS_H
