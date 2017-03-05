/**
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
 * @file EditorMenuController.hpp
 * @brief menu to select between the level or serie editor
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
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * the exception is never caught and the program fails
     */
    EditorMenuController(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~EditorMenuController();

    /**
     * @brief render the editor menu controller
     *
     * @return const ControllerId&
     *
     * no one of the controllers overwritten render() method is noexcept;
     * (check parent declaration for details);
     * they all use SFML methods that are not noexcept
     */
    virtual const ControllerId& render() const & override;

private:

    /**
     * @brief updates the expected controller id according to the selection
     */
    virtual void selectMenuItem() const & noexcept override;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
