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
     * @param context reference to the current context to use
     */
    OfficialSeriesMenuController(
        utils::Context& context
    );

    /**
     * @brief rendering method
     *
     * @param context reference to the current context to use
     *
     * @return unsigned short id of the next screen
     */
    unsigned short render(
        utils::Context& context
    ) override;

private:

    /**
     * @brief defines what to do when the menu items are selected
     */
    void selectMenuItem() override;

    /* the title of the official series list screen is a SFML text surface */
    sf::Text title;

    /* this is specific to the official series menu controller; in fact, we
       need to use the context pointer inside the selectMenuItem() method,
       but this is a pure virtual method inherited from AbstractMenuController;
       all the others menus do not need this pointer in this method; we cannot
       overwritte the parameters of this function only into this class, so we
       create a separated pointer */
    utils::Context& contextPtr;
};

}
}

#endif
