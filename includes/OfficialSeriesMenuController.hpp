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
 * @file OfficialSeriesMenuController.hpp
 * @brief official series menu; display all the official series of the game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_OFFICIALSERIESMENUCONTROLLER_H_
#define MEMORIS_OFFICIALSERIESMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

namespace memoris
{
namespace controllers
{

class OfficialSeriesMenuController : public AbstractMenuController
{
public:

    /**
     * @brief constructor, generates the title of the screen; create unique
     * pointers of the menu items of this screen
     *
     * @param context shared pointer to the current context to use
     */
    OfficialSeriesMenuController(
        const std::shared_ptr<utils::Context>& context
    );

    /**
     * @brief rendering method
     *
     * @param context shared pointer to the current context to use
     *
     * @return unsigned short id of the next screen
     */
    unsigned short render(
        const std::shared_ptr<utils::Context>& context
    ) override;

private:

    /**
     * @brief defines what to do when the menu items are selected
     */
    void selectMenuItem(
        const std::shared_ptr<utils::Context>& context
    ) override;

    /* the title of the official series list screen is a SFML text surface */
    sf::Text title;
};

}
}

#endif
