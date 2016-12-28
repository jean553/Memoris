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
 * @file OpenFileForeground.cpp
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OpenFileForeground.hpp"

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

class OpenFileForeground::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::string&& path
    ) :
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

        /* getFilesFromDirectory() excepts the first parameter to be an array
           of characters, that's why I use c_str(); I could directly send
           an array of characters, but I avoid useless copies of *strings* by
           using the std::string move constructor instead */
        list.setList(
            context,
            utils::getFilesFromDirectory(path.c_str())
        );
    }

    sf::Text explanation;

    widgets::SelectionListWidget list;

    widgets::Cursor cursor;
};

/**
 *
 */
OpenFileForeground::OpenFileForeground(
    const utils::Context& context,
    const std::string&& path
) :
    impl(
        std::make_unique<Impl>(
            context,
            std::move(path)
        )
    )
{
}

/**
 *
 */
OpenFileForeground::~OpenFileForeground() noexcept = default;

/**
 *
 */
void OpenFileForeground::render(const utils::Context& context) const &
{
    context.getSfmlWindow().draw(impl->explanation);

    impl->list.display(context);

    impl->cursor.render(context);
}

/**
 *
 */
const widgets::SelectionListWidget& OpenFileForeground::getList() const &
    noexcept
{
    return impl->list;
}

}
}
