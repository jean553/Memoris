/**
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
 * Cursor widget
 *
 * @file CursorWidget.hpp
 * @brief screen cursor
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CURSOR_WIDGET
#define DEF_CURSOR_WIDGET

#include <SFML/Graphics.hpp>

#include "../utils/Context.hpp"

#define PATH_IMAGE_CURSOR "res/images/cursor.png"

namespace widgets {
class CursorWidget {
public:

    /**
     * Constructor
     */
    CursorWidget();
    ~CursorWidget();

    /**
     * @brief displays the cursor at the same
     * position as the system screen cursor
     *
     * @param context       current context pointer
     */
    void display(utils::Context* context);

private:

    sf::Texture picture;

    sf::Sprite sprite;
};
}

#endif