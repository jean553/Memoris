/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

    Impl(const utils::Context& context) :
        separators(context),
        timer(
            context,
            295.f,
            10.f
        )
    {
        watchingTime = context.getPlayingSerieManager().getWatchingTime();
        lifes = context.getPlayingSerieManager().getLifesAmount();

        foundStarsAmount.setFont(context.getFontsManager().getTextFont());
        foundStarsAmount.setString("0");
        foundStarsAmount.setCharacterSize(fonts::TEXT_SIZE);
        foundStarsAmount.setColor(
            context.getColorsManager().getColorWhite()
        );

        lifesAmount.setFont(context.getFontsManager().getTextFont());
        lifesAmount.setString(std::to_string(lifes));
        lifesAmount.setCharacterSize(fonts::TEXT_SIZE);
        lifesAmount.setColor(context.getColorsManager().getColorWhite());

        time.setFont(context.getFontsManager().getTextFont());
        time.setString(std::to_string(watchingTime));
        time.setCharacterSize(fonts::TEXT_SIZE);
        time.setColor(context.getColorsManager().getColorWhite());

        floor.setFont(context.getFontsManager().getTextFont());
        floor.setString("1");
        floor.setCharacterSize(fonts::TEXT_SIZE);
        floor.setColor(context.getColorsManager().getColorWhite());

        target.setFont(context.getFontsManager().getTextFont());
        target.setString("0");
        target.setCharacterSize(fonts::TEXT_SIZE);
        target.setColor(context.getColorsManager().getColorWhite());

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
GameDashboard::GameDashboard(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /* we set the positions of the text surfaces in this class constructor
       and not in the implementation constructor; in fact, the method
       getHorizontalPositionLessWidth() is necessary for this horizontal
       position calculation; this method is also necessary as a class method
       in order to be used when the content of the surface changes */

    auto& foundStarsAmount = impl->foundStarsAmount;
    constexpr float FOUND_STARS_HORIZONTAL_POSITION {1230.f};
    const auto foundStarsHorizontalPosition = getHorizontalPositionLessWidth(
        FOUND_STARS_HORIZONTAL_POSITION,
        foundStarsAmount
    );

    auto& target = impl->target;
    constexpr float TARGET_STARS_HORIZONTAL_POSITION {1080.f};
    const auto targetHorizontalPosition = getHorizontalPositionLessWidth(
        TARGET_STARS_HORIZONTAL_POSITION,
        target
    );

    auto& lifesAmount = impl->lifesAmount;
    constexpr float LIFES_AMOUNT_HORIZONTAL_POSITION {1230.f};
    const auto lifesAmountHorizontalPosition = getHorizontalPositionLessWidth(
        LIFES_AMOUNT_HORIZONTAL_POSITION,
        lifesAmount
    );

    auto& time = impl->time;
    constexpr float TIME_HORIZONTAL_POSITION {1080.f};
    const auto timeHorizontalPosition = getHorizontalPositionLessWidth(
        TIME_HORIZONTAL_POSITION,
        time
    );

    auto& floor = impl->floor;
    constexpr float FLOOR_HORIZONTAL_POSITION {900.f};
    const auto floorHorizontalPosition = getHorizontalPositionLessWidth(
        FLOOR_HORIZONTAL_POSITION,
        floor
    );

    constexpr float FIRST_LINE_TEXTS_VERTICAL_POSITION {-10.f};

    foundStarsAmount.setPosition(
        foundStarsHorizontalPosition,
        FIRST_LINE_TEXTS_VERTICAL_POSITION
    );

    target.setPosition(
        targetHorizontalPosition,
        FIRST_LINE_TEXTS_VERTICAL_POSITION
    );

    floor.setPosition(
        floorHorizontalPosition,
        FIRST_LINE_TEXTS_VERTICAL_POSITION
    );

    constexpr float SECOND_LINE_TEXTS_VERTICAL_POSITION {35.f};

    lifesAmount.setPosition(
        lifesAmountHorizontalPosition,
        SECOND_LINE_TEXTS_VERTICAL_POSITION
    );

    time.setPosition(
        timeHorizontalPosition,
        SECOND_LINE_TEXTS_VERTICAL_POSITION
    );
}

/**
 *
 */
GameDashboard::~GameDashboard() noexcept = default;

/**
 *
 */
void GameDashboard::display(const utils::Context& context)
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
const unsigned short& GameDashboard::getLifesAmount() const & noexcept
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

/**
 *
 */
const float GameDashboard::getHorizontalPositionLessWidth(
    const float& rightSideHorizontalPosition,
    const sf::Text& sfmlSurface
) const &
{
    return rightSideHorizontalPosition - sfmlSurface.getLocalBounds().width;
}

}
}
