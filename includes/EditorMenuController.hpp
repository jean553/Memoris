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
 * @file EditorMenuController.hpp
 * @brief render the editor menu where the user can select to start the level
 * editor or the serie editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_EDITORMENUCONTROLLER_H_
#define MEMORIS_EDITORMENUCONTROLLER_H_

#include "AbstractMenuController.hpp"

namespace memoris
{
namespace controllers
{

class EditorMenuController : public AbstractMenuController
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context reference to the current context to use
     *
     * context reference is not 'const' because it calls methods that takes
     * a non-const context reference
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    EditorMenuController(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~EditorMenuController() noexcept;

    /**
     * @brief render the editor menu controller
     *
     * @return const ControllerId&
     *
     * not 'const' because it modifies the next controller id attribute
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    virtual const ControllerId& render() & override;

private:

    /**
     * @brief handles menu items selection, declared in the parent class
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
