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
#include "PlayingSerieManager.hpp"
#include "SoundsManager.hpp"
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
#include "Context.hpp"
#include "dimensions.hpp"

#include "HorizontalMirrorAnimation.hpp"
#include "VerticalMirrorAnimation.hpp"
#include "StairsAnimation.hpp"
#include "DiagonalAnimation.hpp"
#include "RotateFloorAnimation.hpp"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
        ),
        editedLevel(context.getEditingLevelManager().getLevel())
    {
        hasWatchingPeriod = (watchingTime != 0);
    }

    sf::Uint32 playerCellAnimationTime {0};
    sf::Uint32 endPeriodStartTime {0};

    short floorMovement {0};

    unsigned short floor {0};
    unsigned short displayedWatchingTime {0};
    unsigned short playingTime {0};
    unsigned short endingScreenSeconds {0};

    bool watchingPeriod {true};
    bool win {false};
    bool hasWatchingPeriod;

    sf::Uint8 playerCellTransparency {64};

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

    const std::shared_ptr<entities::Level>& editedLevel;
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

    impl->watchingPeriod = false;
    impl->timerWidget.start();
}

/**
 *
 */
void GameController::handleAnimation() const &
{
    auto& animation = impl->animation;

    animation->renderAnimation();

    if (animation->isFinished())
    {
        auto& floorMovement = impl->floorMovement;

        if (floorMovement != 0) {

            auto& floor = impl->floor;

            floor += floorMovement;
            impl->dashboard.updateCurrentFloor(floor);

            floorMovement = 0;
        }

        animation.reset();
    }
}

/**
 *
 */
void GameController::handlePlayerCellAnimation() const &
{
    auto& playerCellTransparency = impl->playerCellTransparency;
    constexpr sf::Uint32 PLAYER_CELL_TRANSPARENCY_INTERVAL {64};
    playerCellTransparency += PLAYER_CELL_TRANSPARENCY_INTERVAL;
    impl->level->setPlayerCellTransparency(playerCellTransparency);

    constexpr sf::Uint32 PLAYER_CELL_TRANSPARENCY_MAXIMUM {128};
    if (impl->playerCellTransparency > PLAYER_CELL_TRANSPARENCY_MAXIMUM)
    {
        playerCellTransparency = 0;
    }
}

/**
 *
 */
void GameController::handlePickupEffects() const &
{
    auto& effects = impl->effects;
    auto iterator = effects.begin();

    while (iterator != effects.end())
    {
        if ((*iterator)->isFinished())
        {
            iterator = effects.erase(iterator);
        }
        else
        {
            (*iterator)->render(getContext());
            iterator += 1;
        }
    }
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

    auto& dashboard = impl->dashboard;
    dashboard.display();

    const auto& watchingTimer = impl->watchingTimer;
    const auto& watchingTimerValue = watchingTimer.getWatchingTimerValue();

    if (watchingTimerValue)
    {
        watchingTimer.display();
    }

    const auto& timerWidget = impl->timerWidget;
    timerWidget.display();

    constexpr sf::Int32 ONE_SECOND {1000};
    const auto time = context.getClockMillisecondsTime();
    const auto& level = impl->level;
    const auto& floor = impl->floor;
    const auto& endingScreen = impl->endingScreen;

    auto& lastTime = impl->lastTime;
    auto& animation = impl->animation;
    auto& editedLevel = impl->editedLevel;

    if (time - lastTime > ONE_SECOND)
    {
        if (endingScreen != nullptr)
        {
            auto& endingScreenSeconds = impl->endingScreenSeconds;
            endingScreenSeconds += 1;

            constexpr unsigned short ENDING_SCREEN_SECONDS_DURATION {5};
            if (endingScreenSeconds == ENDING_SCREEN_SECONDS_DURATION)
            {
                if (editedLevel != nullptr)
                {
                    setExpectedControllerId(ControllerId::LevelEditor);
                }
                else if (impl->win)
                {
                    setExpectedControllerId(ControllerId::Game);
                }
                else
                {
                    selectMenuControllerForExit();
                }
            }
        }

        if (watchingTimerValue)
        {
            watchingTimer.decrementWatchingTimer();

            if (watchingTimer.getWatchingTimerValue() == 0)
            {
                if (floor != level->getLastPlayableFloor())
                {
                    watchingTimer.reset();

                    animation = std::make_unique<animations::StairsAnimation>(
                        context,
                        level,
                        floor,
                        animations::StairsAnimation::FloorMoveDirection::Up
                    );

                    impl->floorMovement = 1;
                }
                else
                {
                    startGame();
                }
            }
        }

        const auto timerStarted = timerWidget.isStarted();

        auto& playingTime = impl->playingTime;
        if (
            editedLevel != nullptr or
            timerStarted
        )
        {
            playingTime += 1;
        }

        if (timerStarted)
        {
            timerWidget.decrementPlayingTimer();

            if(
                timerWidget.isTimeOver() and
                impl->hasWatchingPeriod
            )
            {
                endGame();
            }
        }

        lastTime = time;
    }

    if (animation != nullptr)
    {
        handleAnimation();
    }
    else
    {
        level->display(floor);
    }

    constexpr sf::Int32 PLAYER_CELL_ANIMATION_INTERVAL {100};
    auto& lastTimePlayerAnimation = impl->playerCellAnimationTime;
    if (
        not impl->watchingPeriod and
        animation == nullptr and
        time - lastTimePlayerAnimation > PLAYER_CELL_ANIMATION_INTERVAL
    )
    {
        handlePlayerCellAnimation();

        lastTimePlayerAnimation = context.getClockMillisecondsTime();
    }

    if (endingScreen != nullptr)
    {
        endingScreen->render();
    }

    handlePickupEffects();

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
                    animation != nullptr
                )
                {
                    break;
                }

                const bool movementAllowed = level->isPlayerMovementAllowed(
                    event,
                    floor
                );

                if (not movementAllowed)
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

                selectMenuControllerForExit();

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
    using namespace dimensions;

    const auto& level = impl->level;
    const auto& newPlayerCellType = level->getPlayerCellType();
    const auto& context = getContext();
    const auto& dashboard = impl->dashboard;
    const auto& soundsManager = context.getSoundsManager();
    const auto& floor = impl->floor;

    auto& animation = impl->animation;
    auto& floorMovement = impl->floorMovement;

    switch(newPlayerCellType)
    {
    case cells::STAR_CELL:
    {
        soundsManager.playFoundStarSound();

        dashboard.incrementFoundStars();

        const auto& positions = level->getPlayerPosition();

        impl->effects.push_back(
            std::make_unique<utils::PickUpEffect>(
                context.getTexturesManager().getStarTexture(),
                positions
            )
        );

        break;
    }
    case cells::MORE_LIFE_CELL:
    {
        soundsManager.playFoundLifeOrTimeSound();

        dashboard.incrementLifes();

        break;
    }
    case cells::LESS_LIFE_CELL:
    {
        soundsManager.playFoundDeadOrLessTimeSound();

        if (dashboard.getLifes() == 0)
        {
            endGame();

            break;
        }

        dashboard.decrementLifes();

        break;
    }
    case cells::MORE_TIME_CELL:
    {
        soundsManager.playFoundLifeOrTimeSound();

        dashboard.increaseWatchingTime();

        break;
    }
    case cells::LESS_TIME_CELL:
    {
        soundsManager.playFoundDeadOrLessTimeSound();

        constexpr unsigned short MINIMUM_WATCHING_TIME {3};
        if (dashboard.getWatchingTime() != MINIMUM_WATCHING_TIME)
        {
            dashboard.decreaseWatchingTime();
        }

        break;
    }
    case cells::ARRIVAL_CELL:
    {
        if (
            dashboard.getFoundStarsAmount() ==
            level->getStarsAmount()
        )
        {
            impl->win = true;

            const auto& playingSerieManager = context.getPlayingSerieManager();
            const auto& playingTime = impl->playingTime;

            playingSerieManager.addSecondsToPlayingSerieTime(playingTime);

            if (impl->editedLevel != nullptr)
            {
                constexpr unsigned short SECONDS_PER_MINUTE {60};
                level->setSeconds(playingTime % SECONDS_PER_MINUTE);
                level->setMinutes(playingTime / SECONDS_PER_MINUTE);

                setExpectedControllerId(ControllerId::LevelEditor);

                return;
            }

            if (playingSerieManager.hasNextLevel())
            {
                endGame();
            }
            else
            {
                setExpectedControllerId(ControllerId::WinSerie);
            }
        }

        break;
    }
    case cells::STAIRS_UP_CELL:
    case cells::ELEVATOR_UP_CELL:
    {
        unsigned short index = level->getPlayerCellIndex();
        const unsigned short nextFloorIndex = index + CELLS_PER_FLOOR;

        if (nextFloorIndex > CELLS_PER_LEVEL)
        {
            break;
        }

        level->setPlayerCellIndex(nextFloorIndex);

        level->showPlayerCell();

        animation = std::make_unique<animations::StairsAnimation>(
            context,
            level,
            floor,
            animations::StairsAnimation::FloorMoveDirection::Up
        );

        floorMovement = 1;

        break;
    }
    case cells::STAIRS_DOWN_CELL:
    case cells::ELEVATOR_DOWN_CELL:
    {
        unsigned short index = level->getPlayerCellIndex();
        const unsigned short previousFloorIndex = index - CELLS_PER_FLOOR;

        if (previousFloorIndex < 0)
        {
            break;
        }

        level->setPlayerCellIndex(previousFloorIndex);

        level->showPlayerCell();

        animation = std::make_unique<animations::StairsAnimation>(
            context,
            level,
            floor,
            animations::StairsAnimation::FloorMoveDirection::Down
        );

        floorMovement = -1;

        break;
    }
    case cells::HORIZONTAL_MIRROR_CELL:
    {
        animation = std::make_unique<animations::HorizontalMirrorAnimation>(
            context,
            level,
            floor
        );

        break;
    }
    case cells::VERTICAL_MIRROR_CELL:
    {
        animation = std::make_unique<animations::VerticalMirrorAnimation>(
            context,
            level,
            floor
        );

        break;
    }
    case cells::DIAGONAL_CELL:
    {
        animation = std::make_unique<animations::DiagonalAnimation>(
            context,
            level,
            floor
        );

        break;
    }
    case cells::LEFT_ROTATION_CELL:
    {
        animation = std::make_unique<animations::RotateFloorAnimation>(
            context,
            level,
            floor,
            animations::RotateFloorAnimation::MovementDirection::Left
        );

        break;
    }
    case cells::RIGHT_ROTATION_CELL:
    {
        animation = std::make_unique<animations::RotateFloorAnimation>(
            context,
            level,
            floor,
            animations::RotateFloorAnimation::MovementDirection::Right
        );

        break;
    }
    }
}

/**
 *
 */
void GameController::endGame() const &
{
    const auto& context = getContext();
    const auto& soundsManager = context.getSoundsManager();
    auto& endingScreen = impl->endingScreen;

    if (impl->win)
    {
        const auto& serieManager = context.getPlayingSerieManager();
        const auto& dashboard = impl->dashboard;

        soundsManager.playWinLevelSound();

        endingScreen = std::make_unique<utils::WinLevelEndingScreen>(context);

        serieManager.incrementLevelIndex();
        serieManager.setWatchingTime(dashboard.getWatchingTime());
        serieManager.setLifesAmount(dashboard.getLifes());
    }
    else
    {
        context.stopMusic();

        soundsManager.playTimeOverSound();

        endingScreen = std::make_unique<utils::LoseLevelEndingScreen>(context);
    }

    impl->timerWidget.stop();

    impl->endPeriodStartTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void GameController::selectMenuControllerForExit() const & noexcept
{
    const auto& serieType =
        getContext().getPlayingSerieManager().getSerieType();

    if (serieType == managers::PlayingSerieManager::SerieType::Official)
    {
        setExpectedControllerId(ControllerId::OfficialSeriesMenu);

        return;
    }

    setExpectedControllerId(ControllerId::PersonalSeriesMenu);
}

}
}
