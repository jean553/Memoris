/*
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
 * @file GameController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

#include "controllers_ids.hpp"
#include "cells.hpp"
#include "window.hpp"
#include "fonts_sizes.hpp"
#include "controllers.hpp"
#include "PlayingSerieManager.hpp"
#include "SoundsManager.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "GameDashboard.hpp"
#include "TimerWidget.hpp"
#include "WinLevelEndingScreen.hpp"
#include "LoseLevelEndingScreen.hpp"
#include "WatchingTimer.hpp"
#include "TexturesManager.hpp"
#include "Level.hpp"
#include "EditingLevelManager.hpp"
#include "Cell.hpp"
#include "PickUpEffect.hpp"

#include "HorizontalMirrorAnimation.hpp"
#include "VerticalMirrorAnimation.hpp"
#include "StairsAnimation.hpp"
#include "DiagonalAnimation.hpp"
#include "RotateFloorAnimation.hpp"
#include "QuarterRotationAnimation.hpp"

namespace memoris
{
namespace controllers
{

class GameController::Impl
{

public:

    Impl(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& watchingTime
    ) :
        displayedWatchingTime(watchingTime),
        level(level),
        dashboard(
            context,
            level->getStarsAmount()
        ),
        timerWidget(
            context,
            level->getMinutes(),
            level->getSeconds()
        ),
        watchingTimer(
            context,
            watchingTime
        )
    {
        hasWatchingPeriod = (watchingTime != 0);
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
    bool hasWatchingPeriod;

    sf::Uint8 playerCellTransparency {64};
    sf::Uint8 leftLevelsAmountTransparency {255};

    sf::Int8 leftLevelsAmountDirection {-17};

    sf::Int32 lastTimerUpdateTime {0};
    sf::Int32 lastTime {0};

    std::unique_ptr<utils::AbstractLevelEndingScreen> endingScreen {nullptr};
    std::unique_ptr<animations::LevelAnimation> animation {nullptr};

    /* use a pointer here for two reasons: this is faster to copy from one
       method to another, especially after creation into controllers.cpp; we
       have no other choice that creating the Level object into controllers.cpp
       and we still want access it into the controller, so we can not use a
       simple Level reference as the original object would be destroyed */
    std::shared_ptr<entities::Level> level;

    utils::GameDashboard dashboard;

    widgets::TimerWidget timerWidget;

    widgets::WatchingTimer watchingTimer;

    std::vector<std::unique_ptr<utils::PickUpEffect>> effects;
};

/**
 *
 */
GameController::GameController(
    const utils::Context& context,
    const std::shared_ptr<entities::Level>& level,
    const unsigned short& watchingTime
) :
    Controller(context),
    impl(
        std::make_unique<Impl>(
            context,
            level,
            watchingTime
        )
    )
{
    if (not watchingTime)
    {
        startGame();
    }
}

/**
 *
 */
GameController::~GameController() = default;

/**
 *
 */
void GameController::startGame() const &
{
    const auto& level = impl->level;
    level->hideAllCells();
    level->showPlayerCell();

    auto& floor = impl->floor;
    floor = level->getPlayerFloor();
    impl->dashboard.updateCurrentFloor(floor);

    impl->playingPeriod = true;
    impl->watchingPeriod = false;
    impl->timerWidget.setStarted(true);
}

/**
 *
 */
void GameController::handlePlayerMovement(const sf::Event& event) const &
{
    const auto& level = impl->level;

    level->showPlayerCell();

    const auto& playerCellType = level->getPlayerCellType();

    if (
        playerCellType != cells::EMPTY_CELL and
        playerCellType != cells::DEPARTURE_CELL and
        playerCellType != cells::STAIRS_UP_CELL and
        playerCellType != cells::STAIRS_DOWN_CELL and
        playerCellType != cells::ARRIVAL_CELL
    )
    {
        level->emptyPlayerCell();
    }

    switch(event.key.code)
    {
    case sf::Keyboard::Up:
    {
        level->makeTopMovement();

        break;
    }
    case sf::Keyboard::Down:
    {
        level->makeBottomMovement();

        break;
    }
    case sf::Keyboard::Left:
    {
        level->makeLeftMovement();

        break;
    }
    default:
    {
        level->makeRightMovement();

        break;
    }
    }

    level->showPlayerCell();

    executePlayerCellAction();
}

/**
 *
 */
const ControllerId& GameController::render() const &
{
    const auto& context = getContext();

    const auto& watchingTimer = impl->watchingTimer;
    const auto& watchingTimerValue = watchingTimer.getWatchingTimerValue();
    if (watchingTimerValue)
    {
        watchingTimer.display();
    }

    const auto& timerWidget = impl->timerWidget;
    timerWidget.display();

    const auto& playingPeriod = impl->playingPeriod;

    constexpr sf::Int32 ONE_SECOND {1000};
    const auto time = context.getClockMillisecondsTime();
    auto& lastTime = impl->lastTime;
    if (time - lastTime > ONE_SECOND)
    {
        if (watchingTimerValue)
        {
            watchingTimer.decrementWatchingTimer();

            if (watchingTimer.getWatchingTimerValue() == 0)
            {
                startGame();
            }
        }

        if (playingPeriod)
        {
            timerWidget.decrementPlayingTimer();

            impl->playingTime++;

            if(
                timerWidget.isTimeOver() and
                impl->hasWatchingPeriod
            )
            {
                endLevel();
            }
        }

        lastTime = time;
    }

    auto& dashboard = impl->dashboard;
    dashboard.display();

    const auto& level = impl->level;

    if (impl->level->getAnimateFloorTransition())
    {
        impl->level->playFloorTransitionAnimation();
    }
    else if (impl->animation != nullptr)
    {
        impl->animation->renderAnimation();

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
            impl->floor,
            &entities::Cell::display
        );
    }

    constexpr sf::Int32 PLAYER_CELL_ANIMATION_INTERVAL {100};
    if (
        impl->playingPeriod &&
        impl->animation == nullptr &&
        (
            context.getClockMillisecondsTime() -
            impl->playerCellAnimationTime > PLAYER_CELL_ANIMATION_INTERVAL
        )
    )
    {
        constexpr sf::Uint32 PLAYER_CELL_TRANSPARENCY_INTERVAL {64};
        impl->playerCellTransparency += PLAYER_CELL_TRANSPARENCY_INTERVAL;

        impl->level->setPlayerCellTransparency(impl->playerCellTransparency);

        constexpr sf::Uint32 PLAYER_CELL_TRANSPARENCY_MAXIMUM {128};
        if (impl->playerCellTransparency > PLAYER_CELL_TRANSPARENCY_MAXIMUM)
        {
            impl->playerCellTransparency = 0;
        }

        impl->playerCellAnimationTime =
            context.getClockMillisecondsTime();
    }

    if (impl->endingScreen != nullptr)
    {
        impl->endingScreen->render();

        constexpr sf::Int32 END_SCREEN_DISPLAY_DURATION {5000};
        if (
            context.getClockMillisecondsTime() -
            impl->endPeriodStartTime > END_SCREEN_DISPLAY_DURATION
        )
        {
            setExpectedControllerId(
                impl->win ?
                ControllerId::Game:
                ControllerId::MainMenu
            );
        }
    }

    for (auto& effect : impl->effects)
    {
        /* TODO: #1204 we never destroy the allocated finished effects,
           the whole container is simply destroyed at the end of the game;
           this behavior should be improved, effects should be directly destroyed
           when the animation has finished */
        if (effect->isFinished())
        {
            continue;
        }

        effect->render(context);
    }

    setNextControllerId(animateScreenTransition(context));

    auto& event = getEvent();
    while(context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Up:
            case sf::Keyboard::Down:
            case sf::Keyboard::Left:
            case sf::Keyboard::Right:
            {
                if (
                    impl->watchingPeriod or
                    impl->endPeriodStartTime or
                    impl->animation != nullptr
                )
                {
                    break;
                }

                if (
                    not level->isPlayerMovementAllowed(
                        event,
                        impl->floor
                    )
                )
                {
                    context.getSoundsManager().playCollisionSound();

                    break;
                }

                handlePlayerMovement(event);

                break;
            }
            case sf::Keyboard::Escape:
            {
                if (context.getEditingLevelManager().getLevel() != nullptr)
                {
                    setExpectedControllerId(ControllerId::LevelEditor);

                    break;
                }

                setExpectedControllerId(ControllerId::MainMenu);

                break;
            }
            /* TODO: #825 for cheating and dev purposes ;) */
            case sf::Keyboard::P:
            {
                setExpectedControllerId(ControllerId::Game);

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

    return getNextControllerId();
}

/**
 *
 */
void GameController::executePlayerCellAction() const &
{
    const char& newPlayerCellType = impl->level->getPlayerCellType();
    const auto& context = getContext();

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        context.getSoundsManager().playFoundStarSound();

        impl->dashboard.incrementFoundStars();

        impl->effects.push_back(
            std::make_unique<utils::PickUpEffect>(
                context.getTexturesManager().getStarTexture(),
                impl->level->getPlayerCellHorizontalPosition(),
                impl->level->getPlayerCellVerticalPosition()
            )
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

        if (impl->dashboard.getLifes() == 0)
        {
            endLevel();
        }

        if (impl->dashboard.getLifes())
        {
            impl->dashboard.decrementLifes();
        }

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

        constexpr unsigned short MINIMUM_WATCHING_TIME {3};
        if (impl->dashboard.getWatchingTime() != MINIMUM_WATCHING_TIME)
        {
            impl->dashboard.decreaseWatchingTime();
        }

        break;
    }
    case cells::STAIRS_UP_CELL:
    case cells::ELEVATOR_UP_CELL:
    {
        if (impl->level->movePlayerToNextFloor())
        {
            impl->animation = getAnimationByCell(newPlayerCellType);

            impl->movePlayerToNextFloor = true;
        }

        break;
    }
    case cells::STAIRS_DOWN_CELL:
    case cells::ELEVATOR_DOWN_CELL:
    {
        if (impl->level->movePlayerToPreviousFloor())
        {
            impl->animation = getAnimationByCell(newPlayerCellType);

            impl->movePlayerToPreviousFloor = true;
        }

        break;
    }
    case cells::QUARTER_ROTATION_CELL:
    {
        impl->animation = getAnimationByCell(newPlayerCellType);

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
                setExpectedControllerId(ControllerId::LevelEditor);

                return;
            }

            if (playingSerieManager.hasNextLevel())
            {
                endLevel();
            }
            else
            {
                setExpectedControllerId(ControllerId::WinSerie);
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
        impl->animation = getAnimationByCell(newPlayerCellType);

        break;
    }
    }
}

/**
 *
 */
void GameController::watchNextFloorOrHideLevel() const &
{
    const auto& context = getContext();

    if (impl->floor != impl->level->getLastPlayableFloor())
    {
        impl->floor++;

        impl->level->setAnimateFloorTransition(true);

        context.getSoundsManager().playFloorSwitchSound();

        impl->dashboard.updateCurrentFloor(impl->floor);

        impl->displayedWatchingTime =
            context.getPlayingSerieManager().getWatchingTime();

        return;
    }

    startGame();

    context.getSoundsManager().playHideLevelSound();
}

/**
 *
 */
void GameController::endLevel() const &
{
    const auto& context = getContext();

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
        serieManager.setLifesAmount(dashboard.getLifes());
    }
    else
    {
        context.stopMusic();

        context.getSoundsManager().playTimeOverSound();

        impl->endingScreen =
            std::make_unique<utils::LoseLevelEndingScreen>(context);
    }

    impl->playingPeriod = false;

    impl->timerWidget.setStarted(false);

    impl->endPeriodStartTime = context.getClockMillisecondsTime();
}

/**
 *
 */
std::unique_ptr<animations::LevelAnimation> GameController::getAnimationByCell(
    const char& cellType
) const &
{
    const auto& context = getContext();
    const auto& level = impl->level;
    const auto& floor = impl->floor;

    switch(cellType)
    {
    case cells::VERTICAL_MIRROR_CELL:
    {
        return std::make_unique<animations::VerticalMirrorAnimation>(
            context,
            level,
            floor
        );
    }
    case cells::STAIRS_UP_CELL:
    case cells::ELEVATOR_UP_CELL:
    {
        return std::make_unique<animations::StairsAnimation>(
                   context,
                   level,
                   floor,
                   1
               );
    }
    case cells::ELEVATOR_DOWN_CELL:
    case cells::STAIRS_DOWN_CELL:
    {
        return std::make_unique<animations::StairsAnimation>(
                   context,
                   level,
                   floor,
                   -1
               );
    }
    case cells::DIAGONAL_CELL:
    {
        return std::make_unique<animations::DiagonalAnimation>(
            context,
            level,
            floor
        );
    }
    case cells::LEFT_ROTATION_CELL:
    {
        return std::make_unique<animations::RotateFloorAnimation>(
            context,
            level,
            floor,
            -1
        );
    }
    case cells::RIGHT_ROTATION_CELL:
    {
        return std::make_unique<animations::RotateFloorAnimation>(
            context,
            level,
            floor,
            1
        );
    }
    case cells::QUARTER_ROTATION_CELL:
    {
        return std::make_unique<animations::QuarterRotationAnimation>(
            context,
            level,
            floor
        );
    }
    default:
    {
        return std::make_unique<animations::HorizontalMirrorAnimation>(
            context,
            level,
            floor
        );
    }
    }
}

}
}
