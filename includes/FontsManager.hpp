/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @package fonts
 * @brief loads and provides the fonts
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FONTSMANAGER_H_
#define MEMORIS_FONTSMANAGER_H_

#include <memory>

namespace sf
{
class Font;
}

namespace memoris
{
namespace managers
{

class FontsManager
{

public:

    /**
     * @brief constructor, loads each font file one by one, throw an exception
     * if one loading process failed; the exception is not caught and stops
     * the program, an error message is displayed in the console
     *
     * @throw std::invalid_argument throw an exception
     * if the file cannot be loaded
     */
    FontsManager();

    FontsManager(const FontsManager&) = delete;

    FontsManager& operator=(const FontsManager&) = delete;

    /**
     * @brief default destructor
     */
    ~FontsManager();

    /**
     * @brief get title font reference
     *
     * @return const sf::Font&
     */
    const sf::Font& getTitleFont() const & noexcept;

    /**
     * @brief get text font reference
     *
     * @return const sf::Font&
     */
    const sf::Font& getTextFont() const & noexcept;

private:

    /**
     * @brief load the font file from the given path into the font object
     * specified by reference
     *
     * @param font reference to the font object to set
     * @param path constant string of the path to the file to load
     *
     * @throw std::invalid_argument throw an exception
     * if the file cannot be loaded
     *
     * not const because it modifies the SFML fonts attributes, the font
     * parameter is not 'const' because it is modified by the function when
     * loading the file
     *
     * declared static because this method is only internally used to load
     * a font object from a file; it is not supposed to be call according to
     * the instance
     */
    static void loadFontFromFile(
        sf::Font& font,
        const std::string& path
    );

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
