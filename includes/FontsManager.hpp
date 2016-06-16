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
 * @file FontsManager.hpp
 * @brief a class for the unique fonts factory object of the game, all the
 * fonts are loaded from their files when the unique context object is created;
 * we do this to improve performances; each controller, through the context,
 * can get references to each font object, already loaded.
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FONTSMANAGER_H_
#define MEMORIS_FONTSMANAGER_H_

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace fonts
{

class FontsManager
{

public:

    /**
     * @brief constructor, loads each font file one by one, throw an exception
     * if one loading process failed; the exception is not caught and stops
     * the program, an error message is displayed in the console
     */
    FontsManager();

    /**
     * @brief get title font reference
     *
     * @return sf::Font&
     */
    sf::Font& getTitleFont();

    /**
     * @brief get text font reference
     *
     * @return sf::Font&
     */
    sf::Font& getTextFont();

private:

    /* font used for main title and sub-titles */
    const std::string TITLE_FONT = "res/fonts/crystal_regular.ttf";

    /* font used for menu items, buttons and texts */
    const std::string TEXT_FONT = "res/fonts/hi.otf";

    /* SFML font object for the title and sub-titles */
    sf::Font titleFont;

    /* SFML font object for all the texts, messages... */
    sf::Font textFont;
};

}
}

#endif
