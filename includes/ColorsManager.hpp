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
 * @file ColorsManager.hpp
 * @brief a class for the colors manager of the game, all the
 * colors are loaded when the object is created; each controller,
 * through the context, can get the color object it needs
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_COLORSMANAGER_H_
#define MEMORIS_COLORSMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace colors
{

class ColorsManager : public others::NotCopiable
{

public:

    /**
     * @brief constructor, loads each color one by one
     */
    ColorsManager();

    /**
     * @brief returns a reference to the white color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorWhite() const;

    /**
     * @brief returns a reference to the light blue color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorLightBlue() const;

    /**
     * @brief returns a reference to the red color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorRed() const;

    /**
     * @brief returns a reference to the orange color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorBlack() const;

    /**
     * @brief returns a reference to the partial dark grey color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorPartialDarkGrey() const;

    /**
     * @brief returns a reference to the green color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorGreen() const;

    /**
     * @brief returns a reference to the dark green color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorDarkGreen() const;

    /**
     * @brief returns a reference to the purple with low transparency color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorPurpleLowAlpha() const;

    /**
     * @brief returns a copy of the dark grey color
     *
     * @return sf::Color
     */
    const sf::Color& getColorDarkGrey() const;

    /**
     * @brief returns a copy of the blue color
     *
     * @return sf::Color
     */
    sf::Color getColorBlueCopy() const;

    /**
     * @brief returns a copy of the red color
     *
     * @return sf::Color
     */
    sf::Color getColorRedCopy() const;

    /**
     * @brief returns a copy of the white color
     *
     * @return sf::Color
     */
    sf::Color getColorWhiteCopy() const;

    /**
     * @brief returns a copy of the black color
     *
     * @return sf::Color
     */
    sf::Color getColorBlackCopy() const;

private:

    /* NOTE: sf::Uint8 type cannot be constant expressions if
       they are not static. */

    static constexpr sf::Uint8 COLOR_WHITE_RED = 255;
    static constexpr sf::Uint8 COLOR_WHITE_GREEN = 255;
    static constexpr sf::Uint8 COLOR_WHITE_BLUE = 255;

    static constexpr sf::Uint8 COLOR_BLUE_RED = 0;
    static constexpr sf::Uint8 COLOR_BLUE_GREEN = 0;
    static constexpr sf::Uint8 COLOR_BLUE_BLUE = 255;

    static constexpr sf::Uint8 COLOR_RED_RED = 255;
    static constexpr sf::Uint8 COLOR_RED_GREEN = 0;
    static constexpr sf::Uint8 COLOR_RED_BLUE = 0;

    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_RED = 105;
    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_GREEN = 125;
    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_BLUE = 255;

    static constexpr sf::Uint8 COLOR_DARK_GREY_RED = 50;
    static constexpr sf::Uint8 COLOR_DARK_GREY_GREEN = 50;
    static constexpr sf::Uint8 COLOR_DARK_GREY_BLUE = 50;

    static constexpr sf::Uint8 COLOR_BLACK_RED = 0;
    static constexpr sf::Uint8 COLOR_BLACK_GREEN = 0;
    static constexpr sf::Uint8 COLOR_BLACK_BLUE = 0;

    static constexpr sf::Uint8 COLOR_GREEN_RED = 0;
    static constexpr sf::Uint8 COLOR_GREEN_GREEN = 192;
    static constexpr sf::Uint8 COLOR_GREEN_BLUE = 0;

    static constexpr sf::Uint8 COLOR_DARK_GREEN_RED = 0;
    static constexpr sf::Uint8 COLOR_DARK_GREEN_GREEN = 100;
    static constexpr sf::Uint8 COLOR_DARK_GREEN_BLUE = 0;

    static constexpr sf::Uint8 COLOR_PURPLE_RED = 255;
    static constexpr sf::Uint8 COLOR_PURPLE_GREEN = 0;
    static constexpr sf::Uint8 COLOR_PURPLE_BLUE = 255;

    static constexpr sf::Uint8 COLOR_FULL_ALPHA = 255;
    static constexpr sf::Uint8 COLOR_PARTIAL_ALPHA = 225;
    static constexpr sf::Uint8 COLOR_PARTIAL_LOW_ALPHA = 200;

    sf::Color colorWhite;
    sf::Color colorBlue;
    sf::Color colorRed;
    sf::Color colorLightBlue;
    sf::Color colorBlack;
    sf::Color colorPartialDarkGrey;
    sf::Color colorGreen;
    sf::Color colorDarkGreen;
    sf::Color colorPurpleLowAlpha;
    sf::Color colorDarkGrey;
};

}
}

#endif
