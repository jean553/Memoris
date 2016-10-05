/*
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
 * @file GameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

#include "cells.hpp"
#include "window.hpp"
#include "fonts.hpp"
#include "controllers.hpp"
#include "animations.hpp"
#include "PlayingSerieManager.hpp"
#include "SoundsManager.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "GameDashboard.hpp"
#include "WatchingPeriodTimer.hpp"
#include "TutorialWidget.hpp"
#include "TimerWidget.hpp"

namespace memoris
{
namespace controllers
{

class GameController::Impl
{

public:

    Impl(
        utils::Context& context,
        std::shared_ptr<entities::Level> levelPtr
    ) :
        dashboard(context),
        level(levelPtr)
    {
    }

    sf::Uint32 displayLevelTime {0};
    sf::Uint32 playerCellAnimationTime {0};
    sf::Uint32 leftLevelsAmountLastAnimationTime {0};
    sf::Uint32 endPeriodStartTime {0};

    utils::GameDashboard dashboard;

    std::shared_ptr<entities::Level> level;

    std::unique_ptr<animations::LevelAnimation> animation {nullptr};
    std::unique_ptr<widgets::TutorialWidget> tutorialWidget {nullptr};

    bool watchingPeriod {true};
    bool playingPeriod {false};
    bool movePlayerToNextFloor {false};
    bool movePlayerToPreviousFloor {false};
    bool win {false};

    sf::Uint8 playerCellTransparency {64};
    sf::Uint8 leftLevelsAmountTransparency {255};

    sf::Int8 leftLevelsAmountDirection {-17};

    unsigned short floor {0};

    sf::RectangleShape greyFilter;

    sf::Text loseText;
    sf::Text winText;
    sf::Text winInformationText;
    sf::Text leftLevelsAmountText;
};

/**
 *
 */
GameController::GameController(
    utils::Context& context,
    std::shared_ptr<entities::Level> levelPtr
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            levelPtr
        )
    )
{
    /* TODO: #592 this way to do is bad: we got data from one object to
       directly set it as a value of another object, should be refactored */
    impl->dashboard.updateTotalStarsAmountSurface(
        impl->level->getStarsAmount()
    );

    impl->dashboard.getTimerWidget().setMinutesAndSeconds(
        impl->level->getMinutes(),
        impl->level->getSeconds()
    );

    initializeGreyFilter(context);
    initializeLoseText(context);
    initializeWinText(context);

    impl->dashboard.getWatchingPeriodTimer().applyFloorsAmount(
        impl->level->getPlayableFloors()
    );

    if (context.getPlayingSerieManager().getSerieName() == "tutorial")
    {
        impl->tutorialWidget =
            std::make_unique<widgets::TutorialWidget>(context);
    }
}

/**
 *
 */
GameController::~GameController() noexcept = default;

/**
 *
 */
const unsigned short& GameController::render(
    utils::Context& context
) &
{
    if (impl->displayLevelTime == 0)
    {
        impl->displayLevelTime = context.getClockMillisecondsTime();
    }

    impl->dashboard.display(context);

    impl->dashboard.getTimerWidget().display(context);

    if (
        impl->dashboard.getWatchingPeriodTimer().isStarted() &&
        impl->tutorialWidget == nullptr
    )
    {
        impl->dashboard.getWatchingPeriodTimer().display(context);
    }

    if (
        impl->dashboard.getTimerWidget().isFinished() &&
        impl->endPeriodStartTime == 0
    )
    {
        endLevel(context);
    }

    if (impl->level->getAnimateFloorTransition())
    {
        impl->level->playFloorTransitionAnimation(context);
    }
    else if (impl->animation != nullptr)
    {
        impl->animation->renderAnimation(
            context,
            impl->level,
            impl->floor
        );

        if (impl->animation->isFinished())
        {
            if (impl->movePlayerToNextFloor)
            {
                impl->floor++;

                impl->dashboard.updateCurrentFloor(impl->floor);

                impl->movePlayerToNextFloor = false;
            }
            else if (impl->movePlayerToPreviousFloor)
            {
                impl->floor--;

                impl->dashboard.updateCurrentFloor(impl->floor);

                impl->movePlayerToPreviousFloor = false;
            }

            impl->animation.reset();
        }
    }
    else
    {
        impl->level->display(
            context,
            impl->floor,
            &entities::Cell::display
        );
    }

    /* TODO: #547 6000 ms is a default value, should be the actual bonus
       watching time of the player */
    if (
        impl->watchingPeriod &&
        (
            context.getClockMillisecondsTime() -
            impl->displayLevelTime >
            context.getPlayingSerieManager().getWatchingTime() * 1000
        ) &&
        impl->tutorialWidget == nullptr
    )
    {
        watchNextFloorOrHideLevel(context);
    }

    if (
        impl->playingPeriod &&
        impl->animation == nullptr &&
        (
            context.getClockMillisecondsTime() -
            impl->playerCellAnimationTime > 100
        )
    )
    {
        impl->playerCellTransparency += 64;

        impl->level->setPlayerCellTransparency(
            context,
            impl->playerCellTransparency
        );

        if (impl->playerCellTransparency > 128)
        {
            impl->playerCellTransparency = 0;
        }

        impl->playerCellAnimationTime =
            context.getClockMillisecondsTime();
    }

    if (impl->endPeriodStartTime)
    {
        context.getSfmlWindow().draw(impl->greyFilter);

        if (impl->win)
        {
            context.getSfmlWindow().draw(impl->winText);
            context.getSfmlWindow().draw(impl->winInformationText);

            animateLeftLevelsAmount(context);
        }
        else
        {
            context.getSfmlWindow().draw(impl->loseText);
        }

        if (
            context.getClockMillisecondsTime() -
            impl->endPeriodStartTime > 5000
        )
        {
            expectedControllerId = impl->win ?
                                   controllers::GAME_CONTROLLER_ID:
                                   controllers::MAIN_MENU_CONTROLLER_ID;
        }
    }

    if (impl->tutorialWidget != nullptr)
    {
        impl->tutorialWidget->display(context);
    }

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Up:
            {
                handlePlayerMovement(
                    context,
                    -16
                );

                break;
            }
            case sf::Keyboard::Down:
            {
                handlePlayerMovement(
                    context,
                    16
                );

                break;
            }
            case sf::Keyboard::Left:
            {
                handlePlayerMovement(
                    context,
                    -1
                );

                break;
            }
            case sf::Keyboard::Right:
            {
                handlePlayerMovement(
                    context,
                    1
                );

                break;
            }
            case sf::Keyboard::Escape:
            {
                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Return:
            {
                if (impl->tutorialWidget == nullptr)
                {
                    break;
                }

                if (!impl->tutorialWidget->nextFrame())
                {
                    impl->tutorialWidget.reset();
                }
            }
            default:
            {
                break;
            }
            }
        }
        default:
        {
            break;
        }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void GameController::handlePlayerMovement(
    utils::Context& context,
    const short& movement
)
{
    if (
        impl->watchingPeriod ||
        impl->endPeriodStartTime ||
        impl->animation != nullptr
    )
    {
        return;
    }

    if (
        !impl->level->allowPlayerMovement(
            movement,
            impl->floor
        )
    )
    {
        context.getSoundsManager().playCollisionSound();

        return;
    }

    if (impl->level->detectWalls(context, movement))
    {
        context.getSoundsManager().playCollisionSound();

        return;
    }

    emptyPlayerCell(context);

    impl->level->movePlayer(
        context,
        movement
    );

    executePlayerCellAction(context);
}

/**
 *
 */
void GameController::executePlayerCellAction(
    utils::Context& context
)
{
    const char& newPlayerCellType = impl->level->getPlayerCellType();

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        context.getSoundsManager().playFoundStarSound();

        impl->dashboard.incrementFoundStars();

        break;
    }
    case cells::MORE_LIFE_CELL:
    {
        context.getSoundsManager().playFoundLifeOrTimeSound();

        impl->dashboard.incrementLifes();

        break;
    }
    case cells::LESS_LIFE_CELL:
    {
        context.getSoundsManager().playFoundDeadOrLessTimeSound();

        if (impl->dashboard.getLifesAmount() == 0)
        {
            endLevel(context);
        }

        impl->dashboard.decrementLifes();

        break;
    }
    case cells::MORE_TIME_CELL:
    {
        context.getSoundsManager().playFoundLifeOrTimeSound();

        impl->dashboard.increaseWatchingTime();

        break;
    }
    case cells::LESS_TIME_CELL:
    {
        context.getSoundsManager().playFoundDeadOrLessTimeSound();

        impl->dashboard.decreaseWatchingTime();

        break;
    }
    case cells::STAIRS_UP_CELL:
    {
        if (impl->level->movePlayerToNextFloor(context))
        {
            impl->animation = animations::getAnimationByCellType(
                                  context,
                                  newPlayerCellType
                              );

            impl->movePlayerToNextFloor = true;
        }

        break;
    }
    case cells::STAIRS_DOWN_CELL:
    {
        if (impl->level->movePlayerToPreviousFloor(context))
        {
            impl->animation = animations::getAnimationByCellType(
                                  context,
                                  newPlayerCellType
                              );

            impl->movePlayerToPreviousFloor = true;
        }

        break;
    }
    case cells::ARRIVAL_CELL:
    {
        if (
            impl->dashboard.getFoundStarsAmount() ==
            impl->level->getStarsAmount()
        )
        {
            impl->win = true;

            if (context.getPlayingSerieManager().hasNextLevel())
            {
                endLevel(context);
            }
            else
            {
                expectedControllerId = controllers::MAIN_MENU_CONTROLLER_ID;
            }
        }

        break;
    }
    case cells::HORIZONTAL_MIRROR_CELL:
    case cells::VERTICAL_MIRROR_CELL:
    case cells::DIAGONAL_CELL:
    case cells::LEFT_ROTATION_CELL:
    case cells::RIGHT_ROTATION_CELL:
    {
        impl->animation = animations::getAnimationByCellType(
                              context,
                              newPlayerCellType
                          );

        break;
    }
    }
}

/**
 *
 */
void GameController::emptyPlayerCell(
    utils::Context& context
)
{
    const char& playerCellType = impl->level->getPlayerCellType();

    if (
        playerCellType == cells::EMPTY_CELL ||
        playerCellType == cells::DEPARTURE_CELL ||
        playerCellType == cells::STAIRS_UP_CELL ||
        playerCellType == cells::STAIRS_DOWN_CELL ||
        playerCellType == cells::ARRIVAL_CELL ||
        playerCellType == cells::HORIZONTAL_MIRROR_CELL ||
        playerCellType == cells::VERTICAL_MIRROR_CELL ||
        playerCellType == cells::DIAGONAL_CELL ||
        playerCellType == cells::LEFT_ROTATION_CELL ||
        playerCellType == cells::RIGHT_ROTATION_CELL
    )
    {
        return;
    }

    impl->level->emptyPlayerCell(context);
}

/**
 *
 */
void GameController::initializeGreyFilter(
    utils::Context& context
)
{
    impl->greyFilter.setPosition(0.f, 0.f);

    impl->greyFilter.setSize(
        sf::Vector2f(
            window::WIDTH,
            window::HEIGHT
        )
    );

    impl->greyFilter.setFillColor(
        context.getColorsManager().getColorPartialDarkGrey()
    );
}

/**
 *
 */
void GameController::initializeLoseText(
    utils::Context& context
)
{
    impl->loseText.setPosition(
        400.f,
        200.f
    );

    impl->loseText.setString("You Lose !");
    impl->loseText.setCharacterSize(fonts::TITLE_SIZE);
    impl->loseText.setFont(context.getFontsManager().getTextFont());
    impl->loseText.setColor(context.getColorsManager().getColorRed());
}

/**
 *
 */
void GameController::initializeWinText(
    utils::Context& context
)
{
    impl->winText.setPosition(
        480.f,
        100.f
    );
    impl->winText.setString("You Win !");
    impl->winText.setCharacterSize(fonts::TITLE_SIZE);
    impl->winText.setFont(context.getFontsManager().getTextFont());
    impl->winText.setColor(context.getColorsManager().getColorGreen());

    impl->leftLevelsAmountText.setPosition(
        700.f,
        200.f
    );
    impl->leftLevelsAmountText.setString(
        std::to_string(
            context.getPlayingSerieManager().getRemainingLevelsAmount()
        )
    );
    impl->leftLevelsAmountText.setCharacterSize(fonts::LEVELS_COUNTDOWN_SIZE);
    impl->leftLevelsAmountText.setFont(
        context.getFontsManager().getTextFont()
    );
    impl->leftLevelsAmountText.setColor(
        context.getColorsManager().getColorWhite()
    );

    impl->winInformationText.setPosition(
        560.f,
        650.f
    );
    impl->winInformationText.setString("levels left");
    impl->winInformationText.setCharacterSize(fonts::SUB_TITLE_SIZE);
    impl->winInformationText.setFont(context.getFontsManager().getTextFont());
    impl->winInformationText.setColor(
        context.getColorsManager().getColorDarkGreen()
    );
}

/**
 *
 */
void GameController::watchNextFloorOrHideLevel(
    utils::Context& context
)
{
    if (impl->floor != impl->level->getPlayableFloors() - 1)
    {
        impl->floor++;

        impl->level->setAnimateFloorTransition(true);

        context.getSoundsManager().playFloorSwitchSound();

        impl->dashboard.updateCurrentFloor(impl->floor);

        impl->displayLevelTime =
            context.getClockMillisecondsTime();

        return;
    }

    impl->level->hideAllCellsExceptDeparture(context);

    context.getSoundsManager().playHideLevelSound();

    impl->watchingPeriod = false;

    impl->playingPeriod = true;

    impl->floor = impl->level->getPlayerFloor();

    impl->dashboard.updateCurrentFloor(impl->floor);

    impl->dashboard.getTimerWidget().start();
}

/**
 *
 */
void GameController::endLevel(
    utils::Context& context
)
{
    if (impl->win)
    {
        context.getSoundsManager().playWinLevelSound();
    }
    else
    {
        context.stopMusic();

        context.getSoundsManager().playTimeOverSound();
    }

    impl->dashboard.getTimerWidget().stop();

    impl->endPeriodStartTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void GameController::animateLeftLevelsAmount(
    utils::Context& context
)
{
    context.getSfmlWindow().draw(impl->leftLevelsAmountText);

    if (
        context.getClockMillisecondsTime() -
        impl->leftLevelsAmountLastAnimationTime < 50
    )
    {
        return;
    }

    impl->leftLevelsAmountTransparency += impl->leftLevelsAmountDirection;

    if (
        impl->leftLevelsAmountTransparency == 0 ||
        impl->leftLevelsAmountTransparency == 255
    )
    {
        impl->leftLevelsAmountDirection *= -1;
    }

    sf::Color color = context.getColorsManager().getColorWhiteCopy();

    color.a = impl->leftLevelsAmountTransparency;

    impl->leftLevelsAmountText.setColor(color);

    impl->leftLevelsAmountLastAnimationTime =
        context.getClockMillisecondsTime();
}

}
}
