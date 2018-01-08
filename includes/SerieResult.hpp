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
     * @param record the text to set
     *
     * @throw std::bad_alloc the implementation cannot be initialized or
     * std::string::substr() threw because of space leak;
     * this exception is never caught and the program terminates
     *
     * @throws std::invalid_argument the format of serie record is incorrect
     * and the time cannot be calculated; the function throws an exception,
     * this exception is caught and an error message is displayed into the
     * error controller
     */
    SerieResult(const std::string& record);

    SerieResult(const SerieResult&) = delete;

    SerieResult& operator=(const SerieResult&) = delete;

    /**
     * @brief default destructor
     */
    ~SerieResult();

    /**
     * @brief getter of the serie result string
     *
     * @return const std::string&
     */
    const std::string& getString() const & noexcept;

private:

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
