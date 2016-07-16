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
 * @file GameDashboard.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameDashboard.hpp"

#include "fonts.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "TexturesManager.hpp"
#include "Context.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
GameDashboard::GameDashboard() :
    timer(
        295.f,
        10.f
    )
{
    /* create the information label that displays the current amount of found
       stars into the current level */
    foundStarsAmount.setFont(
        fonts::FontsManager::get().getTextFont()
    );
    foundStarsAmount.setString("0");
    foundStarsAmount.setCharacterSize(fonts::TEXT_SIZE);
    foundStarsAmount.setColor(
        colors::ColorsManager::get().getColorWhite()
    );
    foundStarsAmount.setPosition(
        1200.f,
        -10.f
    );

    /* creates the information label that displays the current lifes amount
       of the player */
    lifesAmount.setFont(fonts::FontsManager::get().getTextFont());
    lifesAmount.setString("0");
    lifesAmount.setCharacterSize(fonts::TEXT_SIZE);
    lifesAmount.setColor(colors::ColorsManager::get().getColorWhite());
    lifesAmount.setPosition(
        1200.f,
        35.f
    );

    /* creates the information label that displays the watch time the player
       got until now */
    time.setFont(fonts::FontsManager::get().getTextFont());
    time.setString("0");
    time.setCharacterSize(fonts::TEXT_SIZE);
    time.setColor(colors::ColorsManager::get().getColorWhite());
    time.setPosition(
        1050.f,
        35.f
    );

    /* creates the information label that displays the current player floor;
       the default displayed level is the first one */
    floor.setFont(fonts::FontsManager::get().getTextFont());
    floor.setString("1");
    floor.setCharacterSize(fonts::TEXT_SIZE);
    floor.setColor(colors::ColorsManager::get().getColorWhite());
    floor.setPosition(
        900.f,
        -10.f
    );

    /* creates the information label that indicates the total amount of
       stars available into the level */
    target.setFont(fonts::FontsManager::get().getTextFont());
    target.setString("0");
    target.setCharacterSize(fonts::TEXT_SIZE);
    target.setColor(colors::ColorsManager::get().getColorWhite());
    target.setPosition(
        1050.f,
        -10.f
    );

    /* initialize all the sprites of the dashboard with their textures */

    spriteStar.setTexture(textures::TexturesManager::get().getStarTexture());
    spriteStar.setPosition(
        1250.f,
        0.f
    );

    spriteFloor.setTexture(textures::TexturesManager::get().getFloorTexture());
    spriteFloor.setPosition(
        950.f,
        0.f
    );

    spriteLife.setTexture(textures::TexturesManager::get().getLifeTexture());
    spriteLife.setPosition(
        1250.f,
        50.f
    );

    spriteTarget.setTexture(
        textures::TexturesManager::get().getTargetTexture()
    );
    spriteTarget.setPosition(
        1100.f,
        0.f
    );

    spriteTime.setTexture(textures::TexturesManager::get().getTimeTexture());
    spriteTime.setPosition(
        1100.f,
        50.f
    );
}

/**
 *
 */
void GameDashboard::display()
{
    /* displays the countdown widget */
    timer.display();

    /* displays the information labels of the dashboard */
    utils::Context::get().getSfmlWindow().draw(foundStarsAmount);
    utils::Context::get().getSfmlWindow().draw(lifesAmount);
    utils::Context::get().getSfmlWindow().draw(target);
    utils::Context::get().getSfmlWindow().draw(time);
    utils::Context::get().getSfmlWindow().draw(floor);

    /* displays the dashboard sprites */
    utils::Context::get().getSfmlWindow().draw(spriteStar);
    utils::Context::get().getSfmlWindow().draw(spriteLife);
    utils::Context::get().getSfmlWindow().draw(spriteTarget);
    utils::Context::get().getSfmlWindow().draw(spriteTime);
    utils::Context::get().getSfmlWindow().draw(spriteFloor);
}

}
}
