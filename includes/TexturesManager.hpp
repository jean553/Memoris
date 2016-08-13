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
 * @file TexturesManager.hpp
 * @brief loads and provides the textures assets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TEXTURESMANAGER_H_
#define MEMORIS_TEXTURESMANAGER_H_

#include "NotCopiable.hpp"

#include <SFML/Graphics.hpp>

namespace memoris
{
namespace textures
{

class TexturesManager : public others::NotCopiable
{

public:

    /**
     * @brief constructor, loads each texture one by one, stop if one texture
     * cannot be loaded
     */
    TexturesManager();

    /**
     * @brief getter for the github texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getGithubTexture() const;

    /**
     * @brief getter for the star texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getStarTexture() const;

    /**
     * @brief getter for the life texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getLifeTexture() const;

    /**
     * @brief getter for the target texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTargetTexture() const;

    /**
     * @brief getter for the time texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getTimeTexture() const;

    /**
     * @brief getter for the floor texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getFloorTexture() const;

    /**
     * @brief getter for the hidden texture
     *
     * @return const sf::Texture&
     */
    const sf::Texture& getHiddenTexture() const;

private:

    /* github texture displayed on the main menu */
    sf::Texture githubTexture;

    /* the textures of the game screen */
    sf::Texture starTexture;
    sf::Texture lifeTexture;
    sf::Texture targetTexture;
    sf::Texture timeTexture;
    sf::Texture floorTexture;
};

}
}

#endif
