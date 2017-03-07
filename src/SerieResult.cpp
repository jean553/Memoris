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

    std::string record;

    /* this variable is used to generate the ranking; that's why both of the
       record string and calculated time are wrapped into this class */
    unsigned short time {0};
};

/**
 *
 */
SerieResult::SerieResult() noexcept :
    impl(std::make_unique<Impl>())
{
}

/**
 *
 */
SerieResult::~SerieResult() noexcept = default;

/**
 *
 */
std::string& SerieResult::getString() const & noexcept
{
    return impl->record;
}

/**
 *
 */
void SerieResult::calculateTime() const &
{
    const std::string& record = impl->record;
    const size_t nameTimeSeparatorIndex = record.find(",");

    if (nameTimeSeparatorIndex == std::string::npos)
    {
        /* TODO: #949 we throw std::invalid_argument as it is caught later 
           during serie loading process; this force the error controller to be
           displayed instead but the error message is always the same; we
           should use the invalid_argument message we set here in order to
           give more details to the user */
        throw std::invalid_argument("Incorrect serie file format.");
    }

    /* only keep string content after the comma (only time information) */
    std::string timeString = record.substr(nameTimeSeparatorIndex + 1);

    const size_t minutesSecondsSeparatorIndex = timeString.find(":");

    if (minutesSecondsSeparatorIndex == std::string::npos)
    {
        /* TODO: #949 */
        throw std::invalid_argument("Incorrect serie file format.");
    }

    std::string minutesString = timeString.substr(
        0,
        minutesSecondsSeparatorIndex
    );

    std::string secondsString = timeString.substr(
        minutesSecondsSeparatorIndex + 1
    );

    impl->time = std::stoi(secondsString) + 60 * std::stoi(minutesString);
}

}
}
