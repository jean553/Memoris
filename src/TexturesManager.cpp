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
 * @file TexturesManager.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TexturesManager.hpp"

#include "TexturesLoader.hpp"

namespace memoris
{
namespace textures
{

/**
 *
 */
TexturesManager& TexturesManager::get()
{
    /* create only one time a textures manager instance */
    static TexturesManager singleton;

    /* always return the same textures manager instance */
    return singleton;
}

/**
 *
 */
TexturesManager::TexturesManager()
{
    /* load all the textures one by one; an exception is throw
       and the program stop if one texture cannot be loaded */

    loadTexture(githubTexture, "res/images/fork-me.png");
    loadTexture(starTexture, "res/images/star.png");
    loadTexture(lifeTexture, "res/images/life.png");
    loadTexture(targetTexture, "res/images/target.png");
    loadTexture(timeTexture, "res/images/timer.png");
    loadTexture(floorTexture, "res/images/floor.png");
}

/**
 *
 */
sf::Texture& TexturesManager::getGithubTexture()
{
    return githubTexture;
}

/**
 *
 */
sf::Texture& TexturesManager::getStarTexture()
{
    return starTexture;
}

/**
 *
 */
sf::Texture& TexturesManager::getLifeTexture()
{
    return lifeTexture;
}

/**
 *
 */
sf::Texture& TexturesManager::getTargetTexture()
{
    return targetTexture;
}

/**
 *
 */
sf::Texture& TexturesManager::getTimeTexture()
{
    return timeTexture;
}

/**
 *
 */
sf::Texture& TexturesManager::getFloorTexture()
{
    return floorTexture;
}

}
}
