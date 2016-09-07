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

namespace memoris
{
namespace textures
{

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
    loadTexture(newTexture, "res/images/new.png");
    loadTexture(openTexture, "res/images/open.png");
    loadTexture(saveTexture, "res/images/save.png");
    loadTexture(cursorTexture, "res/images/cursor.png");
    loadTexture(exitTexture, "res/images/exit.png");
    loadTexture(testTexture, "res/images/test.png");
}

/**
 *
 */
const sf::Texture& TexturesManager::getGithubTexture() const
{
    return githubTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getStarTexture() const
{
    return starTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getLifeTexture() const
{
    return lifeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTargetTexture() const
{
    return targetTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTimeTexture() const
{
    return timeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getFloorTexture() const
{
    return floorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getNewTexture() const
{
    return newTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getOpenTexture() const
{
    return openTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getSaveTexture() const
{
    return saveTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getCursorTexture() const
{
    return cursorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getExitTexture() const
{
    return exitTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTestTexture() const
{
    return testTexture;
}

}
}
