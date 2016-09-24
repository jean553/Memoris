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
 * @file NewLevelDialog.cpp
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "NewLevelDialog.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

namespace memoris
{
namespace popups
{

class NewLevelDialog::Impl
{

public:

    sf::Text info;
    sf::Text confirm;
};

/**
 *
 */
NewLevelDialog::NewLevelDialog(utils::Context& context) :
    Dialog(
        context,
        440.f,
        220.f,
        600.f,
        200.f,
        "Confirm ?"
    ),
    impl(std::make_unique<Impl>())
{
    impl->info.setString("Changes will be lost !");
    impl->info.setPosition(
        625.f,
        290.f
    );
    impl->info.setFont(context.getFontsManager().getTextFont());
    impl->info.setCharacterSize(fonts::INFORMATION_SIZE);
    impl->info.setColor(context.getColorsManager().getColorWhite());

    impl->confirm.setString("Enter or escape");
    impl->confirm.setPosition(
        625.f,
        350.f
    );
    impl->confirm.setFont(context.getFontsManager().getTextFont());
    impl->confirm.setCharacterSize(fonts::INFORMATION_SIZE);
    impl->confirm.setColor(context.getColorsManager().getColorWhite());
}

/**
 *
 */
NewLevelDialog::~NewLevelDialog() noexcept = default;

/**
 *
 */
void NewLevelDialog::render(utils::Context& context) &
{
    displayParentContent(context);

    context.getSfmlWindow().draw(impl->info);
    context.getSfmlWindow().draw(impl->confirm);
}

}
}
