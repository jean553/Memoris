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
 * @file TexturesManager.hpp
 * @brief loads and provides the textures assets
 * @package managers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TEXTURESMANAGER_H_
#define MEMORIS_TEXTURESMANAGER_H_

#include <memory>

namespace sf
{
class Texture;
}

namespace memoris
{
namespace managers
{

class TexturesManager
{

public:

    /**
     * @brief constructor, loads each texture one by one, stop if one texture
     * cannot be loaded and throw an exception
     *
     * @throw std::invalid_argument thrown if the texture cannot be loaded,
     * the exception is never caught to voluntary stop the program
     */
    TexturesManager();

    /**
     * @brief default constructor
     */
    ~TexturesManager();

    /**
     * @brief getter for the github texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getGithubTexture() const & noexcept;

    /**
     * @brief getter for the star texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getStarTexture() const & noexcept;

    /**
     * @brief getter for the life texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getLifeTexture() const & noexcept;

    /**
     * @brief getter for the target texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTargetTexture() const & noexcept;

    /**
     * @brief getter for the time texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTimeTexture() const & noexcept;

    /**
     * @brief getter for the floor texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getFloorTexture() const & noexcept;

    /**
     * @brief getter for the new texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getNewTexture() const & noexcept;

    /**
     * @brief getter for the open texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getOpenTexture() const & noexcept;

    /**
     * @brief getter for the save texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getSaveTexture() const & noexcept;

    /**
     * @brief getter for the cursor texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getCursorTexture() const & noexcept;

    /**
     * @brief getter for the exit texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getExitTexture() const & noexcept;

    /**
     * @brief getter for the test texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTestTexture() const & noexcept;

    /**
     * @brief getter for the arrow up texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getArrowUpTexture() const & noexcept;

    /**
     * @brief getter for the arrow down texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getArrowDownTexture() const & noexcept;

    /**
     * @brief getter for the scroll arrow down texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getScrollArrowDownTexture() const & noexcept;

    /**
     * @brief getter for the scroll arrow up texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getScrollArrowUpTexture() const & noexcept;

private:

    /**
     * @brief load a texture from the textures folder
     *
     * @param texture reference to the SFML texture object that has to be set
     * @param path file path of the *.png picture to load
     *
     * @throw std::invalid_argument the given file cannot be opened; the
     * exception is not caught in order to close the program directly if at
     * least one texture cannot be loaded
     *
     * not const because modifies the textures of the object
     */
    void loadTexture(
        sf::Texture& texture,
        const std::string& path
    ) &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
