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
 * @file OpenLevelForeground.cpp
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenLevelForeground.hpp"

#include "Context.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "fonts.hpp"
#include "window.hpp"
#include "SelectionListWidget.hpp"
#include "Cursor.hpp"
#include "DirectoryReader.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace foregrounds
{

class OpenLevelForeground::Impl
{

public:

    Impl(const utils::Context& context) :
        list(context),
        cursor(context)
    {
        explanation.setFont(context.getFontsManager().getTextFont());
        explanation.setString("Select file");
        explanation.setCharacterSize(memoris::fonts::TEXT_SIZE);
        explanation.setColor(context.getColorsManager().getColorWhite());
        explanation.setPosition(
            window::getCenteredSfmlSurfaceHorizontalPosition(explanation),
            50.f
        );

        list.setList(
            context,
            utils::getFilesFromDirectory("data/levels/personals")
        );
    }

    sf::Text explanation;

    widgets::SelectionListWidget list;

    widgets::Cursor cursor;
};

/**
 *
 */
OpenLevelForeground::OpenLevelForeground(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
OpenLevelForeground::~OpenLevelForeground() noexcept = default;

/**
 *
 */
void OpenLevelForeground::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->explanation);

    impl->list.display(context);

    impl->cursor.render(context);
}

/**
 *
 */
const widgets::SelectionListWidget& OpenLevelForeground::getList() const &
    noexcept
{
    return impl->list;
}

}
}
