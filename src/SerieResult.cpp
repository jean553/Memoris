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
 * @file SerieResult.cpp
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieResult.hpp"

#include <string>

namespace memoris
{
namespace entities
{

class SerieResult::Impl
{

public :

    Impl(const std::string& record) :
        record(record)
    {
    }

    std::string record;

    unsigned short time {0};
};

/**
 *
 */
SerieResult::SerieResult(const std::string& record) :
    impl(std::make_unique<Impl>(record))
{
    constexpr char NAME_AND_TIME_SEPARATOR {','};
    const size_t nameSeparatorIndex = record.find(NAME_AND_TIME_SEPARATOR);

    if (nameSeparatorIndex == std::string::npos)
    {
        /* TODO: #949 we throw std::invalid_argument as it is caught later
           during serie loading process; this force the error controller to be
           displayed instead but the error message is always the same; we
           should use the invalid_argument message we set here in order to
           give more details to the user */
        throw std::invalid_argument("Incorrect serie file format.");
    }

    const auto timeStringBeginning = nameSeparatorIndex + 1;
    std::string timeString = record.substr(timeStringBeginning);

    constexpr char MINUTES_AND_SECONDS_SEPARATOR {':'};
    const size_t timeSeparatorIndex = timeString.find(
        MINUTES_AND_SECONDS_SEPARATOR
    );

    if (timeSeparatorIndex == std::string::npos)
    {
        /* TODO: #949 */
        throw std::invalid_argument("Incorrect serie file format.");
    }

    constexpr unsigned short TIME_STRING_BEGINNING {0};
    std::string minutesString = timeString.substr(
        TIME_STRING_BEGINNING,
        timeSeparatorIndex
    );

    const auto secondsStringBeginning = timeSeparatorIndex + 1;
    std::string secondsString = timeString.substr(secondsStringBeginning);

    constexpr unsigned short SECONDS_PER_MINUTE {60};
    impl->time = std::stoi(secondsString) +
        SECONDS_PER_MINUTE * std::stoi(minutesString);
}

/**
 *
 */
SerieResult::~SerieResult() = default;

/**
 *
 */
const std::string& SerieResult::getString() const & noexcept
{
    return impl->record;
}

}
}
