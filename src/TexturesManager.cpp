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
 * @file TexturesManager.cpp
 * @package textures
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TexturesManager.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <stdexcept>

namespace memoris
{
namespace managers
{

class TexturesManager::Impl
{

public:

    sf::Texture cursorTexture;
    sf::Texture githubTexture;
    sf::Texture starTexture;
    sf::Texture lifeTexture;
    sf::Texture targetTexture;
    sf::Texture timeTexture;
    sf::Texture floorTexture;
    sf::Texture newTexture;
    sf::Texture openTexture;
    sf::Texture saveTexture;
    sf::Texture exitTexture;
    sf::Texture testTexture;
    sf::Texture arrowUpTexture;
    sf::Texture arrowDownTexture;
    sf::Texture scrollArrowDownTexture;
    sf::Texture scrollArrowUpTexture;
};

/**
 *
 */
TexturesManager::TexturesManager() :
    impl(std::make_unique<Impl>())
{
    loadTexture(impl->githubTexture, "fork-me");
    loadTexture(impl->starTexture, "star");
    loadTexture(impl->lifeTexture, "life");
    loadTexture(impl->targetTexture, "target");
    loadTexture(impl->timeTexture, "timer");
    loadTexture(impl->floorTexture, "floor");
    loadTexture(impl->newTexture, "new");
    loadTexture(impl->openTexture, "open");
    loadTexture(impl->saveTexture, "save");
    loadTexture(impl->cursorTexture, "cursor");
    loadTexture(impl->exitTexture, "exit");
    loadTexture(impl->testTexture, "test");
    loadTexture(impl->arrowUpTexture, "up");
    loadTexture(impl->arrowDownTexture, "down");
    loadTexture(impl->scrollArrowDownTexture, "scroll_down");
    loadTexture(impl->scrollArrowUpTexture, "scroll_up");
}

/**
 *
 */
TexturesManager::~TexturesManager() = default;

/**
 *
 */
const sf::Texture& TexturesManager::getGithubTexture() const & noexcept
{
    return impl->githubTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getStarTexture() const & noexcept
{
    return impl->starTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getLifeTexture() const & noexcept
{
    return impl->lifeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTargetTexture() const & noexcept
{
    return impl->targetTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTimeTexture() const & noexcept
{
    return impl->timeTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getFloorTexture() const & noexcept
{
    return impl->floorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getNewTexture() const & noexcept
{
    return impl->newTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getOpenTexture() const & noexcept
{
    return impl->openTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getSaveTexture() const & noexcept
{
    return impl->saveTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getCursorTexture() const & noexcept
{
    return impl->cursorTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getExitTexture() const & noexcept
{
    return impl->exitTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getTestTexture() const & noexcept
{
    return impl->testTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getArrowUpTexture() const & noexcept
{
    return impl->arrowUpTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getArrowDownTexture() const & noexcept
{
    return impl->arrowDownTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getScrollArrowDownTexture() const &
    noexcept
{
    return impl->scrollArrowDownTexture;
}

/**
 *
 */
const sf::Texture& TexturesManager::getScrollArrowUpTexture() const & noexcept
{
    return impl->scrollArrowUpTexture;
}

/**
 *
 */
void TexturesManager::loadTexture(
    sf::Texture& texture,
    const std::string& path
) &
{
    if (!texture.loadFromFile("res/images/" + path + ".png"))
    {
        throw std::invalid_argument("Cannot load texture : " + path);
    }
}

}
}
