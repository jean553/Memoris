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

#include <SFML/Graphics/Text.hpp>

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
     * @return const unsigned short& id of the next screen
     */
    virtual const unsigned short& render(utils::Context& context) & override 
        final;

private:

    /**
     * @brief defines what to do when the menu items are selected
     */
    virtual void selectMenuItem() & noexcept override;

    /**
     * @brief returns the name of the serie file to open according to the
     * selected menu item
     *
     * @return const std::string
     *
     * does not return a constant because the returned string is a local
     * literal directly created when return; is called
     */
    const std::string getSerieNameByItemId() const & noexcept;

    /* the title of the official series list screen is a SFML text surface */
    sf::Text title;

    /* we store a context reference as an attribute here; the method
       selectMenuItem is overridden from the parent class; no one of the
       children class needs this method with context usage inside, except this
       class; that's why we keep a reference to the context, in order to use
       it later; by doing like that, we do not need to change the declaration
       of each overridden method and declare variadic parameters... */
    utils::Context& contextPtr;
};

}
}

#endif
