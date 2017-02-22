/**
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
 * @file ColorsManager.hpp
 * @brief a class for the colors manager of the game, all the
 * colors are loaded when the object is created; each controller,
 * through the context, can get the color object it needs
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_COLORSMANAGER_H_
#define MEMORIS_COLORSMANAGER_H_

#include <memory>

namespace sf
{
class Color;
}

namespace memoris
{
namespace managers
{

class ColorsManager
{

public:

    /**
     * @brief constructor, empty, only used to create the implementation object
     */
    ColorsManager() noexcept;

    ColorsManager(const ColorsManager&) = delete;
    ColorsManager& operator=(const ColorsManager&) = delete;

    /**
     * @brief default destructor, empty, only used for forwarding declaration
     */
    ~ColorsManager() noexcept;

    /**
     * @brief returns a reference to the white color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorWhite() const & noexcept;

    /**
     * @brief returns a reference to the white color with low alpha
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorWhiteLowAlpha() const & noexcept;

    /**
     * @brief returns a reference to the light blue color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorLightBlue() const & noexcept;

    /**
     * @brief returns a reference to the blue color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorBlue() const & noexcept;

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
     * @brief returns a reference of the dark grey color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorDarkGrey() const & noexcept;

    /**
     * @brief returns a reference to the alpha blue color
     *
     * @return const sf::Color&
     */
    const sf::Color& getColorBlueLowAlpha() const & noexcept;

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

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
