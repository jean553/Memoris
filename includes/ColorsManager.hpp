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
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_COLORSMANAGER_H_
#define MEMORIS_COLORSMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics/Color.hpp>

namespace memoris
{
namespace managers
{

class ColorsManager : public utils::NotCopiable
{

public:

    /**
     * @brief returns a reference to the white color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorWhite() const & noexcept;

    /**
     * @brief returns a reference to the light blue color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorLightBlue() const & noexcept;

    /**
     * @brief returns a reference to the red color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorRed() const & noexcept;

    /**
     * @brief returns a reference to the orange color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorBlack() const & noexcept;

    /**
     * @brief returns a reference to the partial dark grey color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorPartialDarkGrey() const & noexcept;

    /**
     * @brief returns a reference to the green color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorGreen() const & noexcept;

    /**
     * @brief returns a reference to the dark green color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorDarkGreen() const & noexcept;

    /**
     * @brief returns a reference to the purple with low transparency color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorPurpleLowAlpha() const & noexcept;

    /**
     * @brief returns a copy of the dark grey color
     *
     * @return sf::Color
     */
    const sf::Color& getColorDarkGrey() const & noexcept;

    /* the getter by value do not return constant variables because when
       a color is got by copy, that means the color values will be updated
       into the caller script */

    /**
     * @brief returns a copy of the blue color
     *
     * @return sf::Color
     */
    sf::Color getColorBlueCopy() const & noexcept;

    /**
     * @brief returns a copy of the red color
     *
     * @return sf::Color
     */
    sf::Color getColorRedCopy() const & noexcept;

    /**
     * @brief returns a copy of the white color
     *
     * @return sf::Color
     */
    sf::Color getColorWhiteCopy() const & noexcept;

    /**
     * @brief returns a copy of the black color
     *
     * @return sf::Color
     */
    sf::Color getColorBlackCopy() const & noexcept;

private:

    /* NOTE: sf::Uint8 type cannot be constant expressions if
       they are not static. */

    static constexpr sf::Uint8 COLOR_WHITE_RED {255};
    static constexpr sf::Uint8 COLOR_WHITE_GREEN {255};
    static constexpr sf::Uint8 COLOR_WHITE_BLUE {255};

    static constexpr sf::Uint8 COLOR_BLUE_RED {0};
    static constexpr sf::Uint8 COLOR_BLUE_GREEN {0};
    static constexpr sf::Uint8 COLOR_BLUE_BLUE {255};

    static constexpr sf::Uint8 COLOR_RED_RED {255};
    static constexpr sf::Uint8 COLOR_RED_GREEN {0};
    static constexpr sf::Uint8 COLOR_RED_BLUE {0};

    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_RED {105};
    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_GREEN {125};
    static constexpr sf::Uint8 COLOR_LIGHT_BLUE_BLUE {255};

    static constexpr sf::Uint8 COLOR_DARK_GREY_RED {50};
    static constexpr sf::Uint8 COLOR_DARK_GREY_GREEN {50};
    static constexpr sf::Uint8 COLOR_DARK_GREY_BLUE {50};

    static constexpr sf::Uint8 COLOR_BLACK_RED {0};
    static constexpr sf::Uint8 COLOR_BLACK_GREEN {0};
    static constexpr sf::Uint8 COLOR_BLACK_BLUE {0};

    static constexpr sf::Uint8 COLOR_GREEN_RED {0};
    static constexpr sf::Uint8 COLOR_GREEN_GREEN {192};
    static constexpr sf::Uint8 COLOR_GREEN_BLUE {0};

    static constexpr sf::Uint8 COLOR_DARK_GREEN_RED {0};
    static constexpr sf::Uint8 COLOR_DARK_GREEN_GREEN {100};
    static constexpr sf::Uint8 COLOR_DARK_GREEN_BLUE {0};

    static constexpr sf::Uint8 COLOR_PURPLE_RED {255};
    static constexpr sf::Uint8 COLOR_PURPLE_GREEN {0};
    static constexpr sf::Uint8 COLOR_PURPLE_BLUE {255};

    static constexpr sf::Uint8 COLOR_FULL_ALPHA {255};
    static constexpr sf::Uint8 COLOR_PARTIAL_ALPHA {225};

    /* SFML color cannot be declared as a constant expression, even if it
       is declared as static */

    const sf::Color colorWhite
    {
        COLOR_WHITE_RED,
        COLOR_WHITE_GREEN,
        COLOR_WHITE_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorBlue
    {
        COLOR_BLUE_RED,
        COLOR_BLUE_GREEN,
        COLOR_BLUE_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorRed
    {
        COLOR_RED_RED,
        COLOR_RED_GREEN,
        COLOR_RED_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorLightBlue
    {
        COLOR_LIGHT_BLUE_RED,
        COLOR_LIGHT_BLUE_GREEN,
        COLOR_LIGHT_BLUE_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorBlack
    {
        COLOR_BLACK_RED,
        COLOR_BLACK_GREEN,
        COLOR_BLACK_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorPartialDarkGrey
    {
        COLOR_BLACK_RED,
        COLOR_BLACK_GREEN,
        COLOR_BLACK_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorGreen
    {
        COLOR_GREEN_RED,
        COLOR_GREEN_GREEN,
        COLOR_GREEN_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorDarkGreen
    {
        COLOR_DARK_GREEN_RED,
        COLOR_DARK_GREEN_GREEN,
        COLOR_DARK_GREEN_BLUE,
        COLOR_FULL_ALPHA
    };

    const sf::Color colorPurpleLowAlpha
    {
        COLOR_PURPLE_RED,
        COLOR_PURPLE_GREEN,
        COLOR_PURPLE_BLUE,
        COLOR_PARTIAL_ALPHA
    };

    const sf::Color colorDarkGrey
    {
        COLOR_DARK_GREY_RED,
        COLOR_DARK_GREY_GREEN,
        COLOR_DARK_GREY_BLUE,
        COLOR_FULL_ALPHA
    };
};

}
}

#endif
