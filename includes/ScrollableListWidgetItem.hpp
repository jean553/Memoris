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
 * Keyboard scrollable strings list item
 *
 * @file ScrollableListWidgetItem.hpp
 * @brief a scrollable strings list item with animated arrows
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCROLLABLE_LIST_WIDGET_ITEM
#define DEF_SCROLLABLE_LIST_WIDGET_ITEM

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace widgets
{
class ScrollableListWidgetItem
{
private:

    std::vector<std::string> strList;

    std::vector<sf::Text> txtList;
};
}

#endif
