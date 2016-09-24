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
#include "InputTextWidget.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace popups
{

class SaveLevelDialog::Impl
{

public:

    Impl(utils::Context& context) :
        input(
            context,
            625.f,
            350.f,
            380.f,
            10
        )
    {
    }

    widgets::InputTextWidget input;

    sf::Text info;
};

/**
 *
 */
SaveLevelDialog::SaveLevelDialog(utils::Context& context) :
    Dialog(
        context,
        440.f,
        220.f,
        600.f,
        200.f,
        "Save level"
    ),
    impl(std::make_unique<Impl>(context))
{
    impl->info.setString("Enter the level name:");
    impl->info.setPosition(
        625.f,
        290.f
    );
    impl->info.setFont(context.getFontsManager().getTextFont());
    impl->info.setCharacterSize(fonts::INFORMATION_SIZE);
    impl->info.setColor(context.getColorsManager().getColorWhite());
}

/**
 *
 */
SaveLevelDialog::~SaveLevelDialog() noexcept = default;

/**
 *
 */
void SaveLevelDialog::render(utils::Context& context) &
{
    displayParentContent(context);

    impl->input.display(context);

    context.getSfmlWindow().draw(impl->info);
}

/**
 *
 */
widgets::InputTextWidget& SaveLevelDialog::getInputTextWidget() & noexcept
{
    return impl->input;
}

}
}
