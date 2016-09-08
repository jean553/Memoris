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
 * @package textures
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
    /* load all the textures one by one; an exception is thrown
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
    loadTexture(arrowUpTexture, "res/images/up.png");
    loadTexture(arrowDownTexture, "res/images/down.png");
}

/**
 *
 */
const sf::Texture& TexturesManager::getGithubTexture() const noexcept
{
    return githubTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getStarTexture() const noexcept
{
    return starTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getLifeTexture() const noexcept
{
    return lifeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTargetTexture() const noexcept
{
    return targetTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTimeTexture() const noexcept
{
    return timeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getFloorTexture() const noexcept
{
    return floorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getNewTexture() const noexcept
{
    return newTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getOpenTexture() const noexcept
{
    return openTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getSaveTexture() const noexcept
{
    return saveTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getCursorTexture() const noexcept
{
    return cursorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getExitTexture() const noexcept
{
    return exitTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTestTexture() const noexcept
{
    return testTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getArrowUpTexture() const noexcept
{
    return arrowUpTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getArrowDownTexture() const noexcept
{
    return arrowDownTexture;
}

}
}
