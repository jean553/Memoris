/*
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
 * @file SaveLevelDialog.hpp
 * @brief dialog that is displayed when the player clicks on 'new' button
 * of the level editor
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_NEWLEVELDIALOG_H_
#define MEMORIS_NEWLEVELDIALOG_H_

#include "Dialog.hpp"

#include <memory>

namespace memoris
{
namespace popups
{

class NewLevelDialog : public Dialog
{

public:

    /**
     * @brief constructor, initializes the SFML texture to display
     *
     * @param context constant reference to the current context to use
     */
    NewLevelDialog(const utils::Context& context);

    /**
     * @brief default destructor, empty, declared in order to use forwarding
     * declaration
     */
    ~NewLevelDialog() noexcept;

    /**
     * @brief render the dialog window
     *
     * @param context reference to the current context to use
     *
     * the context is not 'const' because it is modified to
     * render the items
     *
     * not 'const' because it modifies the 'input' attribute
     *
     * not 'noexcept' because it calls SFML functions that are not 'noexcept'
     */
    virtual void render(const utils::Context& context) & override final;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
