/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
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
 * @file ScreenFactory.hpp
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ScreenFactory.hpp"

using namespace factories;

/**
 *
 */
ScreenFactory::ScreenFactory()
{
}

/**
 *
 */
ScreenFactory::~ScreenFactory()
{
}

/**
 *
 */
controllers::Controller* ScreenFactory::getScreenById(
    unsigned char id
) {

    switch(id)
    {
        case 1:
            return new controllers::MainMenuController;
        default:
            return NULL;
    }
}
