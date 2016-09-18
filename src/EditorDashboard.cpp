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
 * @file EditorDashboard.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorDashboard.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
EditorDashboard::EditorDashboard(
    utils::Context& context
) :
    separators(context),
    buttonNew(
        context,
        400.f,
        10.f,
        context.getTexturesManager().getNewTexture()
    ),
    buttonOpen(
        context,
        480.f,
        10.f,
        context.getTexturesManager().getOpenTexture()
    ),
    buttonSave(
        context,
        560.f,
        10.f,
        context.getTexturesManager().getSaveTexture()
    ),
    buttonExit(
        context,
        640.f,
        10.f,
        context.getTexturesManager().getExitTexture()
    ),
    buttonPlay(
        context,
        720.f,
        10.f,
        context.getTexturesManager().getTestTexture()
    ),
    buttonUp(
        context,
        1220.f,
        350.f,
        context.getTexturesManager().getArrowUpTexture()
    ),
    buttonDown(
        context,
        1220.f,
        550.f,
        context.getTexturesManager().getArrowDownTexture()
    )
{
}

/**
 *
 */
void EditorDashboard::display(utils::Context& context)
{
    /* display the separators */
    separators.display(context);

    /* display the buttons */
    buttonNew.display(context);
    buttonOpen.display(context);
    buttonSave.display(context);
    buttonExit.display(context);
    buttonPlay.display(context);
    buttonUp.display(context);
    buttonDown.display(context);
}

/**
 *
 */
unsigned short EditorDashboard::getActionIdBySelectedButton() const
{
    if (buttonExit.isMouseHover())
    {
        return EXIT_ACTION_ID;
    }
    else if (buttonSave.isMouseHover())
    {
        return SAVE_ACTION_ID;
    }
    else if (buttonNew.isMouseHover())
    {
        return NEW_ACTION_ID;
    }
    else if (buttonUp.isMouseHover())
    {
        return FLOOR_UP_ACTION_ID;
    }
    else if (buttonDown.isMouseHover())
    {
        return FLOOR_DOWN_ACTION_ID;
    }

    return 0;
}

}
}
