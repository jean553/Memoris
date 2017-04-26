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
 * @file HorizontalGradient.hpp
 * @brief renders gradients effects horizontally; this effect is used
 * by the serie ending level
 * @package others
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace others
{

class HorizontalGradient
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     */
    HorizontalGradient(const utils::Context& context);

    HorizontalGradient(const HorizontalGradient&) = delete;

    HorizontalGradient& operator=(const HorizontalGradient&) = delete;

    /**
     * @brief default destructor
     */
    ~HorizontalGradient();

    /**
     * @brief renders the gradient effect surfaces
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void render() const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}
