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
 * @file SaveLevelDialog.cpp
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SaveLevelDialog.hpp"

#include "fonts.hpp"

namespace memoris
{
namespace popups
{

/**
 *
 */
SaveLevelDialog::SaveLevelDialog(
    const std::shared_ptr<utils::Context>& context,
    const float& hSize,
    const float& vSize,
    const float& hPosition,
    const float& vPosition,
    const std::string& title
) : Dialog(
        context,
        hSize,
        vSize,
        hPosition,
        vPosition,
        title
    ),
    input(
        context,
        hPosition + 25.f,
        vPosition + 130.f,
        380.f,
        10
    )
{
    /* information text creation */
    info.setString("Enter the level name:");
    info.setPosition(
        hPosition + 20.f,
        vPosition + 70.f
    );
    info.setFont(
        context->getFontsManager().getTextFont()
    );
    info.setCharacterSize(fonts::INFORMATION_SIZE);
    info.setColor(context->getColorsManager().getColorWhite());
}

/**
 *
 */
void SaveLevelDialog::render(const std::shared_ptr<utils::Context>& context)
{
    /* display the basic content of the dialog */
    displayParentContent(context);

    /* display the input */
    input.display(context);

    /* display the information */
    context->getSfmlWindow().draw(info);
}

/**
 *
 */
widgets::InputTextWidget& SaveLevelDialog::getInputTextWidget()
{
    return input;
}

}
}
