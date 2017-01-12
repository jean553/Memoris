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

#include "Context.hpp"
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
        window(context.getSfmlWindow()),
        separators(context),
        timer(context)
    {
        foundStarsAmount.setString("0");
        target.setString("0");
        floor.setString("1");

        const auto& white = context.getColorsManager().getColorWhite();
        foundStarsAmount.setColor(white);
        lifesAmount.setColor(white);
        target.setColor(white);
        time.setColor(white);
        floor.setColor(white);

        const auto& fontSize = fonts::TEXT_SIZE;
        foundStarsAmount.setCharacterSize(fontSize);
        lifesAmount.setCharacterSize(fontSize);
        target.setCharacterSize(fontSize);
        time.setCharacterSize(fontSize);
        floor.setCharacterSize(fontSize);

        const auto& font = context.getFontsManager().getTextFont();
        foundStarsAmount.setFont(font);
        lifesAmount.setFont(font);
        target.setFont(font);
        time.setFont(font);
        floor.setFont(font);

        const auto& playingSerie = context.getPlayingSerieManager();
        watchingTime = playingSerie.getWatchingTime();
        lifes = playingSerie.getLifesAmount();

        lifesAmount.setString(std::to_string(lifes));
        time.setString(std::to_string(watchingTime));

        const auto& texturesManager = context.getTexturesManager();
        spriteStar.setTexture(texturesManager.getStarTexture());
        spriteLife.setTexture(texturesManager.getLifeTexture());
        spriteTarget.setTexture(texturesManager.getTargetTexture());
        spriteTime.setTexture(texturesManager.getTimeTexture());
        spriteFloor.setTexture(texturesManager.getFloorTexture());

        constexpr float FIRST_LINE_ITEMS_VERTICAL_POSITION {0.f};

        constexpr float STAR_SPRITE_HORIZONTAL_POSITION {1250.f};
        spriteStar.setPosition(
            STAR_SPRITE_HORIZONTAL_POSITION,
            FIRST_LINE_ITEMS_VERTICAL_POSITION
        );

        constexpr float TARGET_SPRITE_HORIZONTAL_POSITION {1100.f};
        spriteTarget.setPosition(
            TARGET_SPRITE_HORIZONTAL_POSITION,
            FIRST_LINE_ITEMS_VERTICAL_POSITION
        );

        constexpr float FLOOR_SPRITE_HORIZONTAL_POSITION {950.f};
        spriteFloor.setPosition(
            FLOOR_SPRITE_HORIZONTAL_POSITION,
            FIRST_LINE_ITEMS_VERTICAL_POSITION
        );

        constexpr float SECOND_LINE_ITEMS_VERTICAL_POSITION {50.f};

        constexpr float TIME_SPRITE_HORIZONTAL_POSITION {1100.f};
        spriteTime.setPosition(
            TIME_SPRITE_HORIZONTAL_POSITION,
            SECOND_LINE_ITEMS_VERTICAL_POSITION
        );

        constexpr float LIFE_SPRITE_HORIZONTAL_POSITION {1250.f};
        spriteLife.setPosition(
            LIFE_SPRITE_HORIZONTAL_POSITION,
            SECOND_LINE_ITEMS_VERTICAL_POSITION
        );
    }

    sf::RenderWindow& window;

    sf::Text foundStarsAmount;
    sf::Text target;
    sf::Text floor;
    sf::Text lifesAmount;
    sf::Text time;

    sf::Sprite spriteStar;
    sf::Sprite spriteTarget;
    sf::Sprite spriteFloor;
    sf::Sprite spriteTime;
    sf::Sprite spriteLife;

    utils::LevelSeparators separators;

    widgets::TimerWidget timer;

    unsigned short lifes {0};
    unsigned short watchingTime {0};
    unsigned short foundStars {0};
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

    auto& floor = impl->floor;
    constexpr float FLOOR_HORIZONTAL_POSITION {900.f};
    const auto floorHorizontalPosition = getHorizontalPositionLessWidth(
        FLOOR_HORIZONTAL_POSITION,
        floor
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
GameDashboard::~GameDashboard() = default;

/**
 *
 */
void GameDashboard::display() const &
{
    auto& window = impl->window;

    window.draw(impl->foundStarsAmount);
    window.draw(impl->lifesAmount);
    window.draw(impl->target);
    window.draw(impl->time);
    window.draw(impl->floor);

    window.draw(impl->spriteStar);
    window.draw(impl->spriteLife);
    window.draw(impl->spriteTarget);
    window.draw(impl->spriteTime);
    window.draw(impl->spriteFloor);

    impl->separators.display();
}

/**
 *
 */
const unsigned short& GameDashboard::getLifes() const & noexcept
{
    return impl->lifes;
}

/**
 *
 */
const unsigned short& GameDashboard::getWatchingTime() const & noexcept
{
    return impl->watchingTime;
}

/**
 *
 */
const unsigned short& GameDashboard::getFoundStarsAmount() const & noexcept
{
    return impl->foundStars;
}

/**
 *
 */
void GameDashboard::incrementFoundStars() const &
{
    auto& foundStars = impl->foundStars;
    foundStars++;

    auto& foundStarsAmount = impl->foundStarsAmount;
    updateSfmlTextByNumericValue(
        foundStarsAmount,
        foundStars
    );
}

/**
 *
 */
void GameDashboard::incrementLifes() const &
{
    auto& lifes = impl->lifes;
    lifes++;

    auto& lifesAmount = impl->lifesAmount;
    updateSfmlTextByNumericValue(
        lifesAmount,
        lifes
    );
}

/**
 *
 */
void GameDashboard::decrementLifes() const &
{
    auto& lifes = impl->lifes;
    lifes--;

    auto& lifesAmount = impl->lifesAmount;
    updateSfmlTextByNumericValue(
        lifesAmount,
        lifes
    );
}

/**
 *
 */
void GameDashboard::increaseWatchingTime() const &
{
    auto& watchingTime = impl->watchingTime;
    watchingTime += WATCHING_TIME_UPDATE_STEP;

    auto& time = impl->time;
    updateSfmlTextByNumericValue(
        time,
        watchingTime
    );
}

/**
 *
 */
void GameDashboard::decreaseWatchingTime() const &
{
    auto& watchingTime = impl->watchingTime;
    watchingTime -= WATCHING_TIME_UPDATE_STEP;

    auto& time = impl->time;
    updateSfmlTextByNumericValue(
        time,
        watchingTime
    );
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
void GameDashboard::updateCurrentFloor(const unsigned short& floorIndex)
{
    impl->floor.setString(std::to_string(floorIndex + 1));
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

/**
 *
 */
void GameDashboard::updateSfmlTextByNumericValue(
    sf::Text& sfmlText,
    const unsigned short& numericValue
) const &
{
    sfmlText.setString(std::to_string(numericValue));
}

}
}
