/*
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
 * @file SaveLevelDialog.hpp
 * @brief dialog that is displayed when the 'save' button is pressed down
 * into the level editor
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SAVELEVELDIALOG_H_
#define MEMORIS_SAVELEVELDIALOG_H_

#include "Dialog.hpp"

#include "InputTextWidget.hpp"

namespace memoris
{
namespace popups
{

class SaveLevelDialog : public Dialog
{

public:

    /**
     * @brief constructor, does nothing for now, only pass the variables to
     * the parent constructor
     */
    SaveLevelDialog(
        utils::Context& context,
        const float& hSize,
        const float& vSize,
        const float& hPosition,
        const float& vPosition,
        const std::string& title
    );

    /**
     * @brief render the dialog window
     *
     * @param context reference to the current context to use
     */
    void render(utils::Context& context) override;

    /**
     * @brief getter of the input text widget of the dialog if it has
     *
     * @return widgets::InputTextWidget&
     */
    widgets::InputTextWidget& getInputTextWidget() override;

private:

    /* the input text widget to let the player enters the name of the level */
    widgets::InputTextWidget input;

    /* displayed information */
    sf::Text info;
};

}
}

#endif
