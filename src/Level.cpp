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
 * @file Level.cpp
 * @brief level entity
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "Level.hpp"

#include "Context.hpp"
#include "cells.hpp"
#include "PlayingSerieManager.hpp"
#include "Cell.hpp"

#include <fstream>
#include <algorithm>

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
Level::Level(const utils::Context& context) :
    impl(std::make_unique<Impl>())
{
    for(
        unsigned short index {0};
        index < CELLS_PER_LEVEL;
        index++
    )
    {
        std::unique_ptr<Cell> cell = getCellByType(
            context,
            static_cast<float>(impl->horizontalPositionCursor),
            static_cast<float>(impl->verticalPositionCursor),
            cells::WALL_CELL
        );

        updateCursors();

        impl->cells.push_back(std::move(cell));
    }
}

/**
 *
 */
Level::Level(
    const utils::Context& context,
    const std::string& fileName
) :
    impl(std::make_unique<Impl>())
{
    std::ifstream file(fileName);

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

    for(
        unsigned short index {0}; 
        index < CELLS_PER_LEVEL; 
        index++
    )
    {
        char cellType = cells::EMPTY_CELL;

        if (!file.eof())
        {
            cellType = file.get();
        }

        std::unique_ptr<Cell> cell = getCellByType(
            context,
            static_cast<float>(impl->horizontalPositionCursor),
            static_cast<float>(impl->verticalPositionCursor),
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
}

/**
 *
 */
Level::~Level() noexcept = default;

/**
 *
 */
void Level::display(
    const utils::Context& context,
    const unsigned short& floor,
    void (Cell::*display)(
        const utils::Context&,
        aliases::ConstTransformUniquePtrRef
    ) const &
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
    const utils::Context& context
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
    const utils::Context& context,
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
    const utils::Context& context,
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
        expectedIndex < CELLS_PER_FLOOR * floor or
        expectedIndex >= CELLS_PER_FLOOR * (floor + 1) or
        (
            impl->playerIndex % CELLS_PER_LINE == CELLS_PER_LINE - 1 and
            movement == 1
        ) or
        (impl->playerIndex % CELLS_PER_LINE == 0 && movement == -1)
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
    const utils::Context& context,
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
void Level::emptyPlayerCell(const utils::Context& context)
{
    (*impl->cells[impl->playerIndex]).empty();
    (*impl->cells[impl->playerIndex]).show(context);
}

/**
 *
 */
bool Level::movePlayerToNextFloor(
    const utils::Context& context
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
    const utils::Context& context
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
    const utils::Context& context
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
    const utils::Context& context,
    const float& transparency,
    const unsigned short& floor
) &
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
const std::vector<std::unique_ptr<Cell>>& Level::getCells() const & noexcept
{
    return impl->cells;
}

/**
 *
 */
void Level::createTransform()
{
    impl->transform.reset(new sf::Transform);
}

/**
 *
 */
void Level::rotateAllCells(const short& degrees)
{
    constexpr float FLOOR_CENTER_HORIZONTAL_POSITION {800.f};
    constexpr float FLOOR_CENTER_VERTICAL_POSITION {498.f};
    impl->transform->rotate(
        degrees,
        FLOOR_CENTER_HORIZONTAL_POSITION,
        FLOOR_CENTER_VERTICAL_POSITION
    );
}

/**
 *
 */
void Level::deleteTransform()
{
    impl->transform.reset();
}

/**
 *
 */
void Level::updateCursors() const & noexcept
{
    impl->horizontalPositionCursor++;

    if (impl->horizontalPositionCursor % CELLS_PER_LINE == 0)
    {
        impl->horizontalPositionCursor = 0;

        impl->verticalPositionCursor++;

        if (impl->verticalPositionCursor % CELLS_PER_LINE == 0)
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
    const utils::Context& context,
    const unsigned short& floor,
    const char& type
)
{
    const unsigned short firstCellIndex = floor * 256,
                         lastCellIndex = floor * 256 + 256;

    bool updated = false;

    for(
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator iterator =
            impl->cells.cbegin() + firstCellIndex;
        iterator != impl->cells.cbegin() + lastCellIndex;
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

        if (type == cells::DEPARTURE_CELL)
        {
            impl->playerIndex = std::distance(
                impl->cells.cbegin(),
                iterator
            );
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
void Level::refresh(const utils::Context& context) &
{
    std::for_each(
        impl->cells.begin(),
        impl->cells.end(),
        [&context](const auto& cell) // auto -> std::unique_ptr<entities::Cell>
    {
        cell->setType(cells::WALL_CELL);
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

/**
 *
 */
void Level::showAllCells(const utils::Context& context) const &
{
    auto& cells = impl->cells;

    for (auto& cell : cells)
    {
        cell->show(context);
    }
}

/**
 *
 */
const bool Level::hasOneDepartureAndOneArrival() const & noexcept
{
    unsigned short departureCellsAmount {0};
    unsigned short arrivalCellsAmount {0};

    const auto& cells = impl->cells;
    for (const auto& cell : cells)
    {
        const auto& type = cell->getType();

        if (type == cells::DEPARTURE_CELL)
        {
            departureCellsAmount++;
        }
        else if (type == cells::ARRIVAL_CELL)
        {
            arrivalCellsAmount++;
        }
    }

    return (
        departureCellsAmount == 1 and
        arrivalCellsAmount == 1
    );
}

/**
 *
 */
void Level::initializeEditedLevel() const & noexcept
{
    using CellsIterator =
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator;

    auto& starsAmount = impl->starsAmount;
    starsAmount = 0;

    auto& cells = impl->cells;

    for (
        CellsIterator iterator = cells.cbegin();
        iterator != cells.cend();
        ++iterator
    )
    {
        switch((*iterator)->getType())
        {
        case cells::DEPARTURE_CELL:
        {
            impl->playerIndex = std::distance(
                cells.cbegin(),
                iterator
            );

            break;
        }
        case cells::STAR_CELL:
        {
            starsAmount++;

            break;
        }
        default:
        {
        }
        }
    }
}

/**
 *
 */
const std::vector<char> Level::getCharactersList() const & noexcept
{
    std::vector<char> characters;

    const auto& cells = impl->cells;
    for (const auto& cell : cells)
    {
        characters.push_back(cell->getType());
    }

    return characters;
}

/**
 *
 */
void Level::setCellsFromCharactersList(const std::vector<char>& characters)
    const &
{
    unsigned short index {0};

    auto& cells = impl->cells;
    std::for_each(
        characters.cbegin(),
        characters.cend(),
        [&index, &cells](const char& character)
        {
            cells[index]->setType(character);
            index++;
        }
    );
}

/**
 *
 */
std::unique_ptr<Cell> Level::getCellByType(
    const utils::Context& context,
    const float& horizontalPosition,
    const float& verticalPosition,
    const char type
) const &
{
    constexpr float HORIZONTAL_POSITION_ORIGIN {400.f};
    constexpr float VERTICAL_POSITION_ORIGIN {98.f};
    constexpr float CELL_DIMENSIONS {50.f};

    return std::make_unique<Cell>(
        context,
        HORIZONTAL_POSITION_ORIGIN +
        CELL_DIMENSIONS * horizontalPosition,
        VERTICAL_POSITION_ORIGIN +
        CELL_DIMENSIONS * verticalPosition,
        type
    );
}

}
}
