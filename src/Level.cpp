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
 * @file Level.cpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Level.hpp"

#include "Context.hpp"
#include "cells.hpp"
#include "allocators.hpp"
#include "dimensions.hpp"
#include "PlayingSerieManager.hpp"

#include <fstream>

namespace memoris
{
namespace entities
{

class Level::Impl
{

public:

    std::vector<std::unique_ptr<Cell>> cells;

    unsigned short playerIndex {0};
    unsigned short starsAmount {0};
    unsigned short playableFloors {0};
    unsigned short minutes {0};
    unsigned short seconds {0};

    bool animateFloorTransition {false};

    sf::Uint32 lastAnimationTime {0};

    unsigned short animationColumn {0};
    unsigned short animationFloor {0};
    unsigned short horizontalPositionCursor {0};
    unsigned short verticalPositionCursor {0};

    std::unique_ptr<sf::Transform> transform {nullptr};

    bool emptyFloor {true};
};

/**
 *
 */
Level::Level(
    utils::Context& context,
    const bool loadFromFile
) :
    impl(std::make_unique<Impl>())
{
    if(loadFromFile)
    {
        loadLevelFromFile(context);
    }
    else
    {
        loadEmptyLevel(context);
    }

}

/**
 *
 */
Level::~Level() noexcept = default;

/**
 *
 */
void Level::display(
    utils::Context& context,
    const unsigned short& floor,
    void (Cell::*display)(
        const utils::Context&,
        aliases::ConstTransformUniquePtrRef
    )
) const
{
    const unsigned short firstCellIndex = floor * 256;

    const unsigned short lastCellIndex = floor * 256 + 256;

    for(
        unsigned short index = firstCellIndex;
        index < lastCellIndex;
        index++
    )
    {
        ((*impl->cells[index]).*display)(context, impl->transform);
    }
}

/**
 *
 */
void Level::hideAllCellsExceptDeparture(
    utils::Context& context
)
{
    std::for_each(
        impl->cells.begin(),
        impl->cells.end(),
        [&context](const std::unique_ptr<Cell>& cell)
    {
        if (cell->getType() == cells::DEPARTURE_CELL)
        {
            cell->show(context);

            return;
        }

        cell->hide(context);
    }
    );
}

/**
 *
 */
void Level::setPlayerCellTransparency(
    utils::Context& context,
    const sf::Uint8& alpha
)
{
    (*impl->cells[impl->playerIndex]).setCellColorTransparency(
        context,
        alpha
    );
}

/**
 *
 */
void Level::movePlayer(
    utils::Context& context,
    const short& movement
)
{
    setPlayerCellTransparency(
        context,
        255
    );

    impl->playerIndex += movement;

    (*impl->cells[impl->playerIndex]).show(context);
}

/**
 *
 */
bool Level::allowPlayerMovement(
    const short& movement,
    const unsigned short& floor
) const
{
    short expectedIndex = impl->playerIndex + movement;

    if (
        expectedIndex < 256 * floor ||
        expectedIndex >= (256 * floor) + 256 ||
        (impl->playerIndex % 16 == 19 && movement == 1) ||
        (impl->playerIndex % 16 == 0 && movement == -1)
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
bool Level::detectWalls(
    utils::Context& context,
    const short& movement
) const
{
    if(
        (*impl->cells[impl->playerIndex + movement]).getType() ==
        cells::WALL_CELL
    )
    {
        (*impl->cells[impl->playerIndex + movement]).show(context);

        return true;
    }

    return false;
}

/**
 *
 */
const char& Level::getPlayerCellType() const
{
    return (*impl->cells[impl->playerIndex]).getType();
}

/**
 *
 */
void Level::emptyPlayerCell(utils::Context& context)
{
    (*impl->cells[impl->playerIndex]).empty();
    (*impl->cells[impl->playerIndex]).show(context);
}

/**
 *
 */
bool Level::movePlayerToNextFloor(
    utils::Context& context
)
{
    unsigned short newIndex = impl->playerIndex + 256;

    if (newIndex > 2560)
    {
        return false;
    }

    impl->playerIndex = newIndex;

    (*impl->cells[impl->playerIndex]).show(context);

    return true;
}

/**
 *
 */
bool Level::movePlayerToPreviousFloor(
    utils::Context& context
)
{
    short newIndex = impl->playerIndex - 256;

    if (newIndex < 0)
    {
        return false;
    }

    impl->playerIndex = static_cast<unsigned short>(newIndex);

    (*impl->cells[impl->playerIndex]).show(context);

    return true;
}

/**
 *
 */
const unsigned short& Level::getStarsAmount()
{
    return impl->starsAmount;
}

/**
 *
 */
const unsigned short& Level::getPlayableFloors()
{
    return impl->playableFloors;
}

/**
 *
 */
const unsigned short Level::getPlayerFloor()
{
    return impl->playerIndex / 256;
}

/**
 *
 */
void Level::playFloorTransitionAnimation(
    utils::Context& context
)
{
    for(
        unsigned short i = 0;
        impl->animationFloor * 256 + i < impl->animationFloor * 256 + 256;
        i++
    )
    {
        if (i % 16 < impl->animationColumn)
        {
            (*impl->cells[impl->animationFloor * 256 + i + 256]).display(
                context
            );

            continue;
        }

        if (i % 16 == impl->animationColumn)
        {
            (*impl->cells[impl->animationFloor * 256 + i]).hide(context);
        }

        (*impl->cells[impl->animationFloor * 256 + i]).display(context);
    }

    if (
        context.getClockMillisecondsTime() -
        impl->lastAnimationTime > 25
    )
    {
        impl->animationColumn++;

        if (impl->animationColumn == 16)
        {
            impl->animateFloorTransition = false;

            impl->animationColumn = 0;

            impl->animationFloor++;
        }

        impl->lastAnimationTime = context.getClockMillisecondsTime();
    }
}

/**
 *
 */
void Level::setAnimateFloorTransition(const bool& animate)
{
    impl->animateFloorTransition = animate;
}

/**
 *
 */
const bool& Level::getAnimateFloorTransition()
{
    return impl->animateFloorTransition;
}

/**
 *
 */
const unsigned short& Level::getMinutes() const
{
    return impl->minutes;
}

/**
 *
 */
const unsigned short& Level::getSeconds() const
{
    return impl->seconds;
}

/**
 *
 */
const unsigned short& Level::getPlayerCellIndex() const
{
    return impl->playerIndex;
}

/**
 *
 */
void Level::setPlayerCellIndex(const unsigned short& index)
{
    impl->playerIndex = index;
}

/**
 *
 */
void Level::setCellsTransparency(
    utils::Context& context,
    const float& transparency,
    const unsigned short& floor
)
{
    const unsigned short firstCellIndex = floor * 256;
    const unsigned short lastCellIndex = firstCellIndex + 256;

    for (
        unsigned short index = firstCellIndex;
        index < lastCellIndex;
        index++
    )
    {
        impl->cells[index]->setCellColorTransparency(
            context,
            transparency
        );
    }
}

/**
 *
 */
const std::vector<std::unique_ptr<Cell>>& Level::getCells() const
{
    return impl->cells;
}

/**
 *
 */
void Level::createTransform()
{
    allocators::createDynamicObject(impl->transform);
}

/**
 *
 */
void Level::rotateAllCells(const short& degrees)
{
    impl->transform->rotate(
        degrees,
        dimensions::FLOOR_CENTER_X,
        dimensions::FLOOR_CENTER_Y
    );
}

/**
 *
 */
void Level::deleteTransform()
{
    allocators::deleteDynamicObject(impl->transform);
}

/**
 *
 */
void Level::loadLevelFromFile(utils::Context& context)
{
    std::ifstream file(context.getPlayingSerieManager().getNextLevelName());

    if (!file.is_open())
    {
        /* TODO: #561 - check PlayingSerieManager.cpp for details */
        throw std::invalid_argument("Cannot open the given level file");
    }

    /* FIXME: if the minutes/seconds are not specified or partially specified,
       the behavior is unmanaged */
    std::string min, sec;
    getline(file, min, '\n');
    getline(file, sec, '\n');

    impl->minutes = static_cast<unsigned short>(std::stoi(min));
    impl->seconds = static_cast<unsigned short>(std::stoi(sec));

    for(unsigned short index {0}; index < 2560; index++)
    {
        char cellType = cells::EMPTY_CELL;

        if (!file.eof())
        {
            cellType = file.get();
        }

        std::unique_ptr<Cell> cell = cells::getCellByType(
                                         context,
                                         impl->horizontalPositionCursor,
                                         impl->verticalPositionCursor,
                                         cellType
                                     );

        switch(cellType)
        {
        case cells::DEPARTURE_CELL:
        {
            impl->playerIndex = index;

            break;
        }
        case cells::STAR_CELL:
        {
            impl->starsAmount++;

            break;
        }
        }

        if (
            (
                cellType != cells::EMPTY_CELL &&
                cellType != cells::WALL_CELL
            ) && impl->emptyFloor
        )
        {
            impl->emptyFloor = false;
        }

        updateCursors();

        impl->cells.push_back(std::move(cell));
    }

    /* we do not manually close the std::ifstream object, this object is
       automatically destroyed when it goes out of the scope */
}

/**
 *
 */
void Level::loadEmptyLevel(utils::Context& context)
{
    for(unsigned short index {0}; index < 2560; index++)
    {
        std::unique_ptr<Cell> cell = cells::getCellByType(
                                         context,
                                         impl->horizontalPositionCursor,
                                         impl->verticalPositionCursor,
                                         cells::WALL_CELL
                                     );

        updateCursors();

        impl->cells.push_back(std::move(cell));
    }
}

/**
 *
 */
void Level::updateCursors()
{
    impl->horizontalPositionCursor++;

    if (impl->horizontalPositionCursor % 16 == 0)
    {
        impl->horizontalPositionCursor = 0;

        impl->verticalPositionCursor++;

        if (impl->verticalPositionCursor % 16 == 0)
        {
            impl->verticalPositionCursor = 0;

            if (!impl->emptyFloor)
            {
                impl->playableFloors++;

                impl->emptyFloor = true;
            }
        }
    }
}

/**
 *
 */
const bool Level::updateSelectedCellType(
    utils::Context& context,
    const unsigned short& floor,
    const char& type
)
{
    const unsigned short firstCellIndex = floor * 256,
                         lastCellIndex = floor * 256 + 256;

    bool updated = false;

    for(
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator iterator =
            impl->cells.begin() + firstCellIndex;
        iterator != impl->cells.begin() + lastCellIndex;
        iterator++
    )
    {
        if (!(*iterator)->isMouseHover())
        {
            continue;
        }

        if ((*iterator)->getType() == type)
        {
            break;
        }

        (*iterator)->setType(type);
        (*iterator)->show(context);

        updated = true;

        break;
    }

    return updated;
}

/**
 *
 */
void Level::refresh(utils::Context& context) &
{
    std::for_each(
        impl->cells.begin(),
        impl->cells.end(),
        [&context](const auto& cell) // auto -> std::unique_ptr<entities::Cell>
    {
        cell->setType(cells::EMPTY_CELL);
        cell->show(context);
    }
    );
}

/**
 *
 */
const float& Level::getPlayerCellHorizontalPosition() const & noexcept
{
    return (*impl->cells[impl->playerIndex]).getHorizontalPosition();
}

/**
 *
 */
const float& Level::getPlayerCellVerticalPosition() const & noexcept
{
    return (*impl->cells[impl->playerIndex]).getVerticalPosition();
}

}
}
