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

#include <memory>

namespace sf
{
class Text;
}

namespace memoris
{

namespace controllers
{

class OfficialSeriesMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context reference to the context to use
     *
     * not 'noexcept' because the constructor calls SFML functions that are
     * not noexcept
     */
    OfficialSeriesMenuController(const utils::Context& context);

    /**
     * @brief default destructor, empty, declared only in order to use
     * forwarding declaration
     */
    ~OfficialSeriesMenuController() noexcept;

    /**
     * @brief renders the controller
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short&
     */
    virtual const unsigned short& render(utils::Context& context) & override;

private:

    /**
     * @brief defines what happens when a menu item is selected
     *
     * not 'const' because the the expected controller id is modified
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

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
