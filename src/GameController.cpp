/*
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
#include "TimerWidget.hpp"
#include "WinLevelEndingScreen.hpp"
#include "LoseLevelEndingScreen.hpp"
#include "WatchingTimer.hpp"
#include "PickUpEffectsManager.hpp"
#include "TexturesManager.hpp"
#include "Level.hpp"
#include "EditingLevelManager.hpp"

namespace memoris
{
namespace controllers
{

constexpr float GameController::CELLS_DEFAULT_TRANSPARENCY;

constexpr unsigned short GameController::FIRST_FLOOR_INDEX;

class GameController::Impl
{

public:

    Impl(
        const utils::Context& context,
        const Level& levelPtr,
        const bool& watchLevel
    ) :
        watchingPeriod(watchLevel),
        watchLevel(watchLevel),
        level(levelPtr),
        watchingTimer(context),
        dashboard(context),
        timerText(dashboard.getTimerWidget().getTextSurface())
    {
    }

    sf::Uint32 playerCellAnimationTime {0};
    sf::Uint32 leftLevelsAmountLastAnimationTime {0};
    sf::Uint32 endPeriodStartTime {0};
    sf::Uint32 lastWatchingTimeUpdate {0};

    unsigned short floor {0};
    unsigned short displayedWatchingTime {0};
    unsigned short playingTime {0};

    bool watchingPeriod {true};
    bool playingPeriod {false};
    bool movePlayerToNextFloor {false};
    bool movePlayerToPreviousFloor {false};
    bool win {false};
    bool watchLevel;

    sf::Uint8 playerCellTransparency {64};
    sf::Uint8 leftLevelsAmountTransparency {255};

    sf::Int8 leftLevelsAmountDirection {-17};

    sf::Int32 lastTimerUpdateTime {0};

    std::unique_ptr<utils::LevelEndingScreen> endingScreen {nullptr};
    std::unique_ptr<animations::LevelAnimation> animation {nullptr};

    /* use a pointer here for two reasons: this is faster to copy from one
       method to another, especially after creation into controllers.cpp; we
       have no other choice that creating the Level object into controllers.cpp
       and we still want access it into the controller, so we can not use a
       simple Level reference as the original object would be destroyed */
    Level level;

    widgets::WatchingTimer watchingTimer;

    utils::GameDashboard dashboard;

    utils::PickUpEffectsManager pickUpEffectsManager;

    const sf::Text& timerText;
};

/**
 *
 */
GameController::GameController(
    const utils::Context& context,
    const Level& levelPtr,
    const bool& watchLevel
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            levelPtr,
            watchLevel
        )
    )
{
    auto& level = impl->level;

    /* TODO: #592 this way to do is bad: we got data from one object to
       directly set it as a value of another object, should be refactored */
    impl->dashboard.updateTotalStarsAmountSurface(
        level->getStarsAmount()
    );

    auto& playingSerieManager = context.getPlayingSerieManager();

    impl->displayedWatchingTime = playingSerieManager.getWatchingTime();

    impl->watchingTimer.updateDisplayedAmount(impl->displayedWatchingTime);

    impl->dashboard.getTimerWidget().setMinutesAndSeconds(
        level->getMinutes(),
        level->getSeconds()
    );

    if (not watchLevel)
    {
        level->hideAllCellsExceptDeparture(context);

        level->setCellsTransparency(
            context,
            CELLS_DEFAULT_TRANSPARENCY,
            FIRST_FLOOR_INDEX
        );

        impl->playingPeriod = true;

        auto& floor = impl->floor;
        floor = level->getPlayerFloor();
        impl->dashboard.updateCurrentFloor(floor);
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
    const utils::Context& context
) &
{
    if (impl->watchingPeriod)
    {
        impl->watchingTimer.display(context);
    }

    auto& dashboard = impl->dashboard;
    dashboard.display(context);

    auto& timerWidget = dashboard.getTimerWidget();
    auto& lastTimerUpdateTime = impl->lastTimerUpdateTime;

    if (
        impl->playingPeriod and
        (
            context.getClockMillisecondsTime() -
            lastTimerUpdateTime > ONE_SECOND
        )
    )
    {
        if (impl->watchLevel)
        {
            timerWidget.render();
        }

        impl->playingTime++;

        lastTimerUpdateTime = context.getClockMillisecondsTime();
    }

    context.getSfmlWindow().draw(impl->timerText);

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

    if (impl->endingScreen != nullptr)
    {
        impl->endingScreen->render(context);

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

    if (
        impl->watchingPeriod and
        context.getClockMillisecondsTime() -
        impl->lastWatchingTimeUpdate > 1000
    )
    {
        if (impl->displayedWatchingTime == 1)
        {
            watchNextFloorOrHideLevel(context);
        }
        else
        {
            impl->displayedWatchingTime--;
        }

        impl->watchingTimer.updateDisplayedAmount(impl->displayedWatchingTime);

        impl->lastWatchingTimeUpdate = context.getClockMillisecondsTime();
    }

    impl->pickUpEffectsManager.renderAllEffects(context);

    if(impl->dashboard.getTimerWidget().isFinished())
    {
        endLevel(context);
    }

    nextControllerId = animateScreenTransition(context);

    while(window.pollEvent(event))
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
                if (context.getEditingLevelManager().getLevel() != nullptr)
                {
                    expectedControllerId = LEVEL_EDITOR_CONTROLLER_ID;

                    break;
                }

                expectedControllerId = MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* TODO: #825 for cheating and dev purposes ;) */
            case sf::Keyboard::P:
            {
                expectedControllerId = controllers::GAME_CONTROLLER_ID;

                break;
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
    const utils::Context& context,
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
    const utils::Context& context
)
{
    const char& newPlayerCellType = impl->level->getPlayerCellType();

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        context.getSoundsManager().playFoundStarSound();

        impl->dashboard.incrementFoundStars();

        impl->pickUpEffectsManager.addPickUpEffect(
            context.getTexturesManager().getStarTexture(),
            impl->level->getPlayerCellHorizontalPosition(),
            impl->level->getPlayerCellVerticalPosition()
        );

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
    case cells::ELEVATOR_UP_CELL:
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
    case cells::ELEVATOR_DOWN_CELL:
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
    case cells::QUARTER_ROTATION_CELL:
    {
        impl->animation = animations::getAnimationByCellType(
            context,
            newPlayerCellType
        );

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

            const auto& editingLevelManager = context.getEditingLevelManager();
            const auto& editedLevel = editingLevelManager.getLevel();

            const auto& playingSerieManager = context.getPlayingSerieManager();
            playingSerieManager.addSecondsToPlayingSerieTime(
                impl->playingTime
            );

            if (editedLevel != nullptr)
            {
                expectedControllerId = LEVEL_EDITOR_CONTROLLER_ID;

                return;
            }

            if (playingSerieManager.hasNextLevel())
            {
                endLevel(context);
            }
            else
            {
                expectedControllerId = controllers::WIN_SERIE_CONTROLLER_ID;
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
    const utils::Context& context
)
{
    const char& playerCellType = impl->level->getPlayerCellType();

    if (
        playerCellType == cells::EMPTY_CELL ||
        playerCellType == cells::DEPARTURE_CELL ||
        playerCellType == cells::STAIRS_UP_CELL ||
        playerCellType == cells::STAIRS_DOWN_CELL ||
        playerCellType == cells::ARRIVAL_CELL
    )
    {
        return;
    }

    impl->level->emptyPlayerCell(context);
}

/**
 *
 */
void GameController::watchNextFloorOrHideLevel(
    const utils::Context& context
)
{
    if (impl->floor != impl->level->getPlayableFloors() - 1)
    {
        impl->floor++;

        impl->level->setAnimateFloorTransition(true);

        context.getSoundsManager().playFloorSwitchSound();

        impl->dashboard.updateCurrentFloor(impl->floor);

        impl->displayedWatchingTime =
            context.getPlayingSerieManager().getWatchingTime();

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
void GameController::endLevel(const utils::Context& context)
{
    if (impl->win)
    {
        // auto -> const managers::PlayingSerieManager&
        const auto& serieManager = context.getPlayingSerieManager();

        // auto -> const utils::GameDashboard&
        const auto& dashboard = impl->dashboard;

        context.getSoundsManager().playWinLevelSound();

        impl->endingScreen =
            std::make_unique<utils::WinLevelEndingScreen>(context);

        serieManager.incrementLevelIndex();
        serieManager.setWatchingTime(dashboard.getWatchingTime());
        serieManager.setLifesAmount(dashboard.getLifesAmount());
    }
    else
    {
        context.stopMusic();

        context.getSoundsManager().playTimeOverSound();

        impl->endingScreen =
            std::make_unique<utils::LoseLevelEndingScreen>(context);
    }

    impl->dashboard.getTimerWidget().stop();

    impl->endPeriodStartTime = context.getClockMillisecondsTime();
}

}
}
