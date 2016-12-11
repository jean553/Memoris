/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file SerieResult.hpp
 * @brief contains all the serie result properties
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SERIERESULT_H_
#define MEMORIS_SERIERESULT_H_

#include <memory>

namespace memoris
{
namespace entities
{

class SerieResult
{

public:

    /**
     * @brief default constructor, just initializes the implementation
     */
    SerieResult() noexcept;

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SerieResult() noexcept;

    /**
     * @brief getter of the serie result string; does not return a constant
     * reference; this reference is used to modify the value
     *
     * @return std::string&
     */
    std::string& getString() const & noexcept;

    /**
     * @brief calculate the total time from the record string; this is a
     * separated function as we never set the std::string record, but we
     * use the std::getline() function instead that just takes a string
     * reference as a parameter (during the reading serie file process)
     *
     * @throws std::invalid_argument the format of serie record is incorrect
     * and the time cannot be calculated; the function throws an exception,
     * this exception is caught and an error message is displayed into the
     * error controller
     */
    void calculateTime() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
