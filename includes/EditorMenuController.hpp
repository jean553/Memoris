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
 * @file EditorMenuController.hpp
 * @brief render the editor menu where the user can select to start the level
 * editor or the serie editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITORMENUCONTROLLER_H_
#define MEMORIS_EDITORMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace controllers
{

class EditorMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, initializes the title and the menu items
     *
     * @param context reference to the current context to use
     */
    EditorMenuController(utils::Context& context);

    /**
     * @brief render the editor menu controller, returns the id of the next
     * controller to render
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(utils::Context& context) & override
    final;

private:

    /**
     * @brief handles menu items selection, declared in the parent class
     */
    virtual void selectMenuItem() & noexcept override;

    /* the SFML title surface of the menu */
    sf::Text title;
};

}
}

#endif
