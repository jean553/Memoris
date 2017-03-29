/*
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief one best result for a serie (each serie comes with three results);
 * there is a numeric time in order to sort the results
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
     * @brief constructor
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    SerieResult();

    SerieResult(const SerieResult&) = delete;

    SerieResult& operator=(const SerieResult&) = delete;

    /**
     * @brief default destructor
     */
    ~SerieResult();

    /**
     * @brief getter of the serie result string
     *
     * @return std::string&
     *
     * TODO: #1117 we do not return a constant reference
     * as the returned reference is modified when loading a serie
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
     *
     * TODO: #1117 I plane to get rid of this function
     * so it is not refactored yet
     */
    void calculateTime() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
