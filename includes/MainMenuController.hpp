/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file MainMenuController.hpp
 * @brief main menu, first displayed controller after program starts
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_MAINMENUCONTROLLER_H_
#define MEMORIS_MAINMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

namespace memoris
{

namespace controllers
{

class MainMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     */
    MainMenuController(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~MainMenuController();

    /**
     * @brief render the main menu controller
     *
     * @return const ControllerId&
     */
    virtual const ControllerId& render() const & override;

private:

    /**
     * @brief update the color of the title
     *
     * not 'noexcept' because it calls the SFML function setColor() which is
     * not noexcept
     */
    void animateTitleColor() const &;

    /**
     * @brief overwrite the parent method, defines which controller
     * is called when one menu item is selected
     *
     * not 'const' because it modifies the expected controller id
     */
    virtual void selectMenuItem() const & noexcept override;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
