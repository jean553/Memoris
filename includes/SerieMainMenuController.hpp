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
 * @file SerieMainMenuController.hpp
 * @brief the main menu for the serie selection; the player can choose between
 * the official series and the personal series
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SERIEMAINMENUCONTROLLER_H_
#define MEMORIS_SERIEMAINMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

namespace memoris
{
namespace controllers
{

class SerieMainMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, creates the title surface and generate the
     * menu items unique pointers of the menu
     *
     * @param context shared pointer to the current context to use
     */
    SerieMainMenuController(const std::shared_ptr<utils::Context>& context);

    /**
     * @brief render the serie editor screen
     *
     * @param context shared pointer to the current context to use
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render(
        const std::shared_ptr<utils::Context>& context
    ) override;

private:

    /* the serie main menu controller main SFML title */
    sf::Text title;

    /**
     * @brief overwrite the parent method; defines which constroller is called
     * when one menu item is selected
     */
    void selectMenuItem() override;
};

}
}

#endif
