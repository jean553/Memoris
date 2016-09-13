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

#include "window.hpp"
#include "fonts.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
GameDashboard::GameDashboard(utils::Context& context) :
    separators(context)
{
    watchingTime = context.getPlayingSerieManager().getWatchingTime();

    /* create the information label that displays the current amount of found
       stars into the current level */
    foundStarsAmount.setFont(context.getFontsManager().getTextFont());
    foundStarsAmount.setString("0");
    foundStarsAmount.setCharacterSize(fonts::TEXT_SIZE);
    foundStarsAmount.setColor(
        context.getColorsManager().getColorWhite()
    );
    foundStarsAmount.setPosition(
        1200.f,
        -10.f
    );

    /* creates the information label that displays the current lifes amount
       of the player */
    lifesAmount.setFont(context.getFontsManager().getTextFont());
    lifesAmount.setString("0");
    lifesAmount.setCharacterSize(fonts::TEXT_SIZE);
    lifesAmount.setColor(context.getColorsManager().getColorWhite());
    lifesAmount.setPosition(
        1200.f,
        35.f
    );

    /* creates the information label that displays the watch time the player
       got until now */
    time.setFont(context.getFontsManager().getTextFont());
    time.setString(std::to_string(watchingTime));
    time.setCharacterSize(fonts::TEXT_SIZE);
    time.setColor(context.getColorsManager().getColorWhite());
    time.setPosition(
        1050.f,
        35.f
    );

    /* creates the information label that displays the current player floor;
       the default displayed level is the first one */
    floor.setFont(context.getFontsManager().getTextFont());
    floor.setString("1");
    floor.setCharacterSize(fonts::TEXT_SIZE);
    floor.setColor(context.getColorsManager().getColorWhite());
    floor.setPosition(
        900.f,
        -10.f
    );

    /* creates the information label that indicates the total amount of
       stars available into the level */
    target.setFont(context.getFontsManager().getTextFont());
    target.setString("0");
    target.setCharacterSize(fonts::TEXT_SIZE);
    target.setColor(context.getColorsManager().getColorWhite());
    target.setPosition(
        1050.f,
        -10.f
    );

    /* initialize all the sprites of the dashboard with their textures */

    spriteStar.setTexture(context.getTexturesManager().getStarTexture());
    spriteStar.setPosition(
        1250.f,
        0.f
    );

    spriteFloor.setTexture(context.getTexturesManager().getFloorTexture());
    spriteFloor.setPosition(
        950.f,
        0.f
    );

    spriteLife.setTexture(context.getTexturesManager().getLifeTexture());
    spriteLife.setPosition(
        1250.f,
        50.f
    );

    spriteTarget.setTexture(
        context.getTexturesManager().getTargetTexture()
    );
    spriteTarget.setPosition(
        1100.f,
        0.f
    );

    spriteTime.setTexture(context.getTexturesManager().getTimeTexture());
    spriteTime.setPosition(
        1100.f,
        50.f
    );
}

/**
 *
 */
void GameDashboard::display(utils::Context& context)
{
    /* displays the information labels of the dashboard */
    context.getSfmlWindow().draw(foundStarsAmount);
    context.getSfmlWindow().draw(lifesAmount);
    context.getSfmlWindow().draw(target);
    context.getSfmlWindow().draw(time);
    context.getSfmlWindow().draw(floor);

    /* displays the dashboard sprites */
    context.getSfmlWindow().draw(spriteStar);
    context.getSfmlWindow().draw(spriteLife);
    context.getSfmlWindow().draw(spriteTarget);
    context.getSfmlWindow().draw(spriteTime);
    context.getSfmlWindow().draw(spriteFloor);

    /* display the separators */
    separators.display(context);
}

/**
 *
 */
void GameDashboard::incrementFoundStars()
{
    /* increment the amount of found stars */
    foundStars++;

    /* update the SFML text surface that displays the amount of found stars */
    foundStarsAmount.setString(std::to_string(foundStars));
}

/**
 *
 */
void GameDashboard::incrementLifes()
{
    /* increment the lifes amount */
    lifes++;

    /* update the SFML text surface that displays the amount of lifes */
    lifesAmount.setString(std::to_string(lifes));
}

/**
 *
 */
void GameDashboard::decrementLifes()
{
    /* TODO: #587 we check if the amount of lifes is equal to 0 but we should
       not do it this way and here; we only prevent the value to be
       automatically set to 65665 if the lifes amount is already equal to 0;
       the 'lose' process should be called instead and the game should
       finish */
    if (lifes == 0)
    {
        return;
    }

    /* decrement the lifes amount */
    lifes--;

    /* update the SFML text surface that displays the amount of lifes */
    lifesAmount.setString(std::to_string(lifes));
}

/**
 *
 */
void GameDashboard::increaseWatchingTime()
{
    /* increase the amount of watching time; this amount of 3 seconds; */
    watchingTime += 3;

    /* update the SFML text surface that displays the amount of watching
       time */
    time.setString(std::to_string(watchingTime));
}

/**
 *
 */
void GameDashboard::decreaseWatchingTime()
{
    /* do not decrease the amount of watching time if this watching time
       is already equal to 3; the minimum watching time is 3 */
    if (watchingTime == 3)
    {
        /* ends the process */
        return;
    }

    /* decrease the amount of watching time */
    watchingTime -= 3;

    /* update the SFML text surface that displays the amount of watching
       time */
    time.setString(std::to_string(watchingTime));
}

/**
 *
 */
const unsigned short& GameDashboard::getFoundStarsAmount()
{
    return foundStars;
}

/**
 *
 */
void GameDashboard::updateTotalStarsAmountSurface(const unsigned short& amount)
{
    /* update the displayed stars amount inside the game dashboard according
       to the passed amount */
    target.setString(std::to_string(amount));
}

/**
 *
 */
const unsigned short& GameDashboard::getLifesAmount()
{
    return lifes;
}

/**
 *
 */
void GameDashboard::updateCurrentFloor(const unsigned short& floorIndex)
{
    floor.setString(std::to_string(floorIndex + 1));
}

/**
 *
 */
const unsigned short& GameDashboard::getWatchingTime() const
{
    return watchingTime;
}

}
}
