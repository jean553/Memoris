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
 * @file EditorDashboard.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorDashboard.hpp"

#include "TexturesManager.hpp"
#include "Context.hpp"
#include "LevelSeparators.hpp"
#include "Button.hpp"

namespace memoris
{
namespace utils
{

class EditorDashboard::Impl
{

public:

    Impl(const utils::Context& context) :
        separators(context),
        buttonNew(
            context,
            400.f,
            10.f,
            context.getTexturesManager().getNewTexture()
        ),
        buttonSave(
            context,
            480.f,
            10.f,
            context.getTexturesManager().getSaveTexture()
        ),
        buttonExit(
            context,
            560.f,
            10.f,
            context.getTexturesManager().getExitTexture()
        ),
        buttonPlay(
            context,
            640.f,
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

    utils::LevelSeparators separators;

    widgets::Button buttonNew;
    widgets::Button buttonSave;
    widgets::Button buttonExit;
    widgets::Button buttonPlay;
    widgets::Button buttonUp;
    widgets::Button buttonDown;
};

/**
 *
 */
EditorDashboard::EditorDashboard(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
EditorDashboard::~EditorDashboard() noexcept = default;

/**
 *
 */
void EditorDashboard::display(const utils::Context& context) const &
{
    impl->separators.display();

    impl->buttonNew.display(context);
    impl->buttonSave.display(context);
    impl->buttonExit.display(context);
    impl->buttonPlay.display(context);
    impl->buttonUp.display(context);
    impl->buttonDown.display(context);
}

/**
 *
 */
const EditorDashboard::Action EditorDashboard::getActionIdBySelectedButton() 
    const &
{
    if (impl->buttonExit.isMouseHover())
    {
        return Action::EXIT;
    }
    else if (impl->buttonSave.isMouseHover())
    {
        return Action::SAVE;
    }
    else if (impl->buttonNew.isMouseHover())
    {
        return Action::NEW;
    }
    else if (impl->buttonUp.isMouseHover())
    {
        return Action::UP;
    }
    else if (impl->buttonDown.isMouseHover())
    {
        return Action::DOWN;
    }
    else if (impl->buttonPlay.isMouseHover())
    {
        return Action::PLAY;
    }

    return Action::NO_ACTION;
}

}
}
