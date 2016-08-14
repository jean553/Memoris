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
 * @file FontsManager.cpp
 * @brief a class for the unique fonts factory object of the game, all the
 * fonts are loaded from their files when the unique context object is created;
 * we do this to improve performances; each controller, through the context,
 * can get references to each font object, already loaded.
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FontsManager.hpp"
#include "errors.hpp"

namespace memoris
{
namespace fonts
{

/* font used for main title and sub-titles */
const std::string FontsManager::TITLE_FONT = "res/fonts/crystal_regular.ttf";

/* font used for menu items, buttons and texts */
const std::string FontsManager::TEXT_FONT = "res/fonts/hi.otf";

/**
 *
 */
FontsManager::FontsManager()
{
    /* try to open each font file one by one; in case
       of an error, we stop immediately to try to open
       and we directly throw an exception: the program
       must be terminated immediately; that's why we
       even do not try to open the next file; the
       exception is not caught, the program stops
       with the open font error message */
    if(!titleFont.loadFromFile(TITLE_FONT))
    {
        throw std::invalid_argument(
            errors::OPEN_FONT_ERROR_PREFIX + TITLE_FONT
        );
    }
    if(!textFont.loadFromFile(TEXT_FONT))
    {
        throw std::invalid_argument(
            errors::OPEN_FONT_ERROR_PREFIX + TEXT_FONT
        );
    }
}

/**
 *
 */
const sf::Font& FontsManager::getTitleFont() const
{
    return titleFont;
}

/**
 *
 */
const sf::Font& FontsManager::getTextFont() const
{
    return textFont;
}

}
}
