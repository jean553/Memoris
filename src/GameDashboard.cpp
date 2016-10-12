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
#include "PlayingSerieManager.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "TexturesManager.hpp"
#include "LevelSeparators.hpp"
#include "TimerWidget.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace memoris
{
namespace utils
{

class GameDashboard::Impl
{

public:

    Impl(utils::Context& context) :
        separators(context),
        timer(
            context,
            295.f,
            10.f
        )
    {
        watchingTime = context.getPlayingSerieManager().getWatchingTime();

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

        lifesAmount.setFont(context.getFontsManager().getTextFont());
        lifesAmount.setString("0");
        lifesAmount.setCharacterSize(fonts::TEXT_SIZE);
        lifesAmount.setColor(context.getColorsManager().getColorWhite());
        lifesAmount.setPosition(
            1200.f,
            35.f
        );

        time.setFont(context.getFontsManager().getTextFont());
        time.setString(std::to_string(watchingTime));
        time.setCharacterSize(fonts::TEXT_SIZE);
        time.setColor(context.getColorsManager().getColorWhite());
        time.setPosition(
            1050.f,
            35.f
        );

        floor.setFont(context.getFontsManager().getTextFont());
        floor.setString("1");
        floor.setCharacterSize(fonts::TEXT_SIZE);
        floor.setColor(context.getColorsManager().getColorWhite());
        floor.setPosition(
            900.f,
            -10.f
        );

        target.setFont(context.getFontsManager().getTextFont());
        target.setString("0");
        target.setCharacterSize(fonts::TEXT_SIZE);
        target.setColor(context.getColorsManager().getColorWhite());
        target.setPosition(
            1050.f,
            -10.f
        );

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

    sf::Text foundStarsAmount;
    sf::Text lifesAmount;
    sf::Text target;
    sf::Text time;
    sf::Text floor;

    sf::Sprite spriteStar;
    sf::Sprite spriteLife;
    sf::Sprite spriteTarget;
    sf::Sprite spriteTime;
    sf::Sprite spriteFloor;

    /* TODO: #579 this amount is 0 by default for now, but the default value
       should be extracted from the serie file if the level is the first one of
       the serie; it it is not the first one, the amount of lifes should be the
       lifes left the user has */
    unsigned short lifes {0};
    unsigned short watchingTime;
    unsigned short foundStars {0};

    utils::LevelSeparators separators;

    widgets::TimerWidget timer;
};

/**
 *
 */
GameDashboard::GameDashboard(utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
GameDashboard::~GameDashboard() noexcept = default;

/**
 *
 */
void GameDashboard::display(utils::Context& context)
{
    context.getSfmlWindow().draw(impl->foundStarsAmount);
    context.getSfmlWindow().draw(impl->lifesAmount);
    context.getSfmlWindow().draw(impl->target);
    context.getSfmlWindow().draw(impl->time);
    context.getSfmlWindow().draw(impl->floor);

    context.getSfmlWindow().draw(impl->spriteStar);
    context.getSfmlWindow().draw(impl->spriteLife);
    context.getSfmlWindow().draw(impl->spriteTarget);
    context.getSfmlWindow().draw(impl->spriteTime);
    context.getSfmlWindow().draw(impl->spriteFloor);

    impl->separators.display(context);
}

/**
 *
 */
void GameDashboard::incrementFoundStars()
{
    impl->foundStars++;

    impl->foundStarsAmount.setString(
        std::to_string(impl->foundStars)
    );
}

/**
 *
 */
void GameDashboard::incrementLifes()
{
    impl->lifes++;

    impl->lifesAmount.setString(
        std::to_string(impl->lifes)
    );
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
    if (impl->lifes == 0)
    {
        return;
    }

    impl->lifes--;

    impl->lifesAmount.setString(
        std::to_string(impl->lifes)
    );
}

/**
 *
 */
void GameDashboard::increaseWatchingTime()
{
    impl->watchingTime += 3;

    impl->time.setString(
        std::to_string(impl->watchingTime)
    );
}

/**
 *
 */
void GameDashboard::decreaseWatchingTime()
{
    if (impl->watchingTime == 3)
    {
        return;
    }

    impl->watchingTime -= 3;

    impl->time.setString(
        std::to_string(impl->watchingTime)
    );
}

/**
 *
 */
const unsigned short& GameDashboard::getFoundStarsAmount()
{
    return impl->foundStars;
}

/**
 *
 */
void GameDashboard::updateTotalStarsAmountSurface(const unsigned short& amount)
{
    impl->target.setString(std::to_string(amount));
}

/**
 *
 */
const unsigned short& GameDashboard::getLifesAmount()
{
    return impl->lifes;
}

/**
 *
 */
void GameDashboard::updateCurrentFloor(const unsigned short& floorIndex)
{
    impl->floor.setString(std::to_string(floorIndex + 1));
}

/**
 *
 */
const unsigned short& GameDashboard::getWatchingTime() const
{
    return impl->watchingTime;
}

/**
 *
 */
widgets::TimerWidget& GameDashboard::getTimerWidget() const & noexcept
{
    return impl->timer;
}

}
}
