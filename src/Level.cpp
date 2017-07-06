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

#include "cells.hpp"
#include "Cell.hpp"

#include <fstream>

namespace memoris
{
namespace entities
{

constexpr unsigned short CELLS_PER_FLOOR {256};
constexpr unsigned short CELLS_PER_LINE {16};
constexpr unsigned short CELLS_PER_LEVEL {2560};

class Level::Impl
{

public:

    Impl(const utils::Context& context) :
        context(context)
    {
    }

    std::vector<std::unique_ptr<Cell>> cells;

    unsigned short playerIndex {0};
    unsigned short starsAmount {0};
    unsigned short minutes {0};
    unsigned short seconds {0};
    unsigned short lastPlayableCell {0};

    bool animateFloorTransition {false};

    sf::Uint32 lastAnimationTime {0};

    std::unique_ptr<sf::Transform> transform {nullptr};

    const utils::Context& context;
};

/**
 *
 */
Level::Level(const utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    unsigned short row {0}, column {0};

    for(
        unsigned short index {0};
        index < CELLS_PER_LEVEL;
        index++
    )
    {
        std::unique_ptr<Cell> cell = getCellByType(
            static_cast<float>(column),
            static_cast<float>(row),
            cells::WALL_CELL
        );

        incrementRowAndColumnIndexes(
            row,
            column
        );

        impl->cells.push_back(std::move(cell));
    }
}

/**
 *
 */
Level::Level(
    const utils::Context& context,
    const std::string& filePath
) :
    impl(std::make_unique<Impl>(context))
{
    std::ifstream file(filePath);

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

    unsigned short row {0}, column {0};

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
            static_cast<float>(column),
            static_cast<float>(row),
            cellType
        );

        incrementRowAndColumnIndexes(
            row,
            column
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

        if (cellType != cells::WALL_CELL)
        {
            impl->lastPlayableCell = index;
        }

        impl->cells.push_back(std::move(cell));
    }
}

/**
 *
 */
Level::~Level() = default;

/**
 *
 */
void Level::incrementRowAndColumnIndexes(
    unsigned short& row,
    unsigned short& column
) const & noexcept
{
    column += 1;
    if (column % CELLS_PER_LINE == 0)
    {
        column = 0;
        row += 1;

        if (row % CELLS_PER_LINE == 0)
        {
            row = 0;
        }
    }
}

/**
 *
 */
const unsigned short Level::getLastPlayableFloor() const & noexcept
{
    return impl->lastPlayableCell / CELLS_PER_FLOOR;
}

/**
 *
 */
void Level::showPlayerCell() const &
{
    (*impl->cells[impl->playerIndex]).show(impl->context);
}

/**
 *
 */
void Level::hideAllCells() const &
{
    const auto& context = impl->context;

    std::for_each(
        impl->cells.begin(),
        impl->cells.end(),
        [&context](const std::unique_ptr<Cell>& cell)
    {
        cell->hide(context);
    }
    );
}

/**
 *
 */
void Level::makeTopMovement() const & noexcept
{
    const short TOP_MOVE {-16};
    impl->playerIndex += TOP_MOVE;
}

/**
 *
 */
void Level::makeBottomMovement() const & noexcept
{
    const short BOTTOM_MOVE {16};
    impl->playerIndex += BOTTOM_MOVE;
}

/**
 *
 */
void Level::makeLeftMovement() const & noexcept
{
    const short LEFT_MOVE {-1};
    impl->playerIndex += LEFT_MOVE;
}

/**
 *
 */
void Level::makeRightMovement() const & noexcept
{
    const short RIGHT_MOVE {1};
    impl->playerIndex += RIGHT_MOVE;
}

/**
 *
 */
const std::pair<float, float> Level::getPlayerPosition() const & noexcept
{
    const auto& cell = (*impl->cells[impl->playerIndex]);
    return std::make_pair(
        cell.getHorizontalPosition(),
        cell.getVerticalPosition()
    );
}

/**
 *
 */
const bool Level::isPlayerMovementAllowed(
    const sf::Event& event,
    const unsigned short& floor
) const &
{
    unsigned short expectedIndex = impl->playerIndex;
    short movement {0};

    switch(event.key.code)
    {
    case sf::Keyboard::Up:
    {
        constexpr float TOP_MOVE {-16};
        expectedIndex += TOP_MOVE;
        movement = TOP_MOVE;

        break;
    }
    case sf::Keyboard::Down:
    {
        constexpr float BOTTOM_MOVE {16};
        expectedIndex += BOTTOM_MOVE;
        movement = BOTTOM_MOVE;

        break;
    }
    case sf::Keyboard::Left:
    {
        constexpr float LEFT_MOVE {-1};
        expectedIndex += LEFT_MOVE;
        movement = LEFT_MOVE;

        break;
    }
    default:
    {
        constexpr float RIGHT_MOVE {1};
        expectedIndex += RIGHT_MOVE;
        movement = RIGHT_MOVE;

        break;
    }
    }

    const auto& nextCell = *impl->cells[expectedIndex];
    if(nextCell.getType() == cells::WALL_CELL)
    {
        nextCell.show(impl->context);

        return false;
    }

    if (
        expectedIndex < CELLS_PER_FLOOR * floor or
        expectedIndex >= CELLS_PER_FLOOR * (floor + 1) or
        (
            expectedIndex % CELLS_PER_LINE == CELLS_PER_LINE - 1 and
            movement == 1
        ) or
        (
            expectedIndex % CELLS_PER_LINE == 0 and
            movement == -1
        )
    )
    {
        return false;
    }

    return true;
}

/**
 *
 */
void Level::display(const unsigned short& floor) const &
{
    constexpr unsigned short CELLS_PER_FLOOR {256};
    const unsigned short firstCellIndex = floor * CELLS_PER_FLOOR;
    const unsigned short lastCellIndex = (floor + 1) * CELLS_PER_FLOOR;

    for(
        unsigned short index = firstCellIndex;
        index < lastCellIndex;
        index++
    )
    {
        (*impl->cells[index]).display(
            impl->context,
            impl->transform
        );
    }
}

/**
 *
 */
void Level::setPlayerCellTransparency(const sf::Uint8& alpha) const &
{
    (*impl->cells[impl->playerIndex]).setCellColorTransparency(
        impl->context,
        alpha
    );
}

/**
 *
 */
const char& Level::getPlayerCellType() const &
{
    return (*impl->cells[impl->playerIndex]).getType();
}

/**
 *
 */
void Level::emptyPlayerCell() const &
{
    (*impl->cells[impl->playerIndex]).empty();
    (*impl->cells[impl->playerIndex]).show(impl->context);
}

/**
 *
 */
const unsigned short& Level::getStarsAmount() const & noexcept
{
    return impl->starsAmount;
}

/**
 *
 */
const unsigned short Level::getPlayerFloor() const & noexcept
{
    return impl->playerIndex / 256;
}

/**
 *
 */
const unsigned short& Level::getMinutes() const & noexcept
{
    return impl->minutes;
}

/**
 *
 */
const unsigned short& Level::getSeconds() const & noexcept
{
    return impl->seconds;
}

/**
 *
 */
const unsigned short& Level::getPlayerCellIndex() const & noexcept
{
    return impl->playerIndex;
}

/**
 *
 */
void Level::setPlayerCellIndex(const unsigned short& index) const & noexcept
{
    impl->playerIndex = index;
}

/**
 *
 */
void Level::setCellsTransparency(
    const float& transparency,
    const unsigned short& floor
) const &
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
            impl->context,
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
void Level::createTransform() const &
{
    impl->transform.reset(new sf::Transform);
}

/**
 *
 */
void Level::deleteTransform() const & noexcept
{
    impl->transform.reset();
}

/**
 *
 */
void Level::rotateAllCells(const short& degrees) const &
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
const bool Level::updateSelectedCellType(
    const unsigned short& floor,
    const char& type
) const &
{
    const unsigned short firstCellIndex = floor * CELLS_PER_FLOOR;
    const unsigned short lastCellIndex = (floor + 1) * CELLS_PER_FLOOR;

    auto updated = false;

    for(
        auto iterator = impl->cells.cbegin() + firstCellIndex;
        iterator != impl->cells.cbegin() + lastCellIndex;
        iterator++
    )
    {
        const auto& cell = **iterator;

        if (!cell.isMouseHover())
        {
            continue;
        }

        if (cell.getType() == type)
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

        cell.setType(type);
        cell.show(impl->context);

        updated = true;

        break;
    }

    return updated;
}

/**
 *
 */
void Level::allCellsAsWalls() const &
{
    const auto& cells = impl->cells;

    std::for_each(
        cells.begin(),
        cells.end(),
        [this](const auto& cell)
    {
        cell->setType(cells::WALL_CELL);
        cell->show(impl->context);
    }
    );
}

/**
 *
 */
void Level::showAllCells() const &
{
    const auto& cells = impl->cells;

    for (const auto& cell : cells)
    {
        cell->show(impl->context);
    }
}

/**
 *
 */
const bool Level::hasOneDepartureAndOneArrival() const & noexcept
{
    unsigned short departureCellsAmount {0};
    unsigned short arrivalCellsAmount {0};

    /* this method browses the whole cells list of the level;
       we could have created two booleans indicating if the departure cell
       and the arrival cell exists; however this feature is only required
       for the level editor, so we would have created two useless attributes
       in case of the level is used into the game (and not into the editor) */

    const auto& cells = impl->cells;
    for (const auto& cell : cells)
    {
        const auto& type = cell->getType();

        if (type == cells::DEPARTURE_CELL)
        {
            departureCellsAmount += 1;
        }
        else if (type == cells::ARRIVAL_CELL)
        {
            arrivalCellsAmount += 1;
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
void Level::initializeEditedLevel() const &
{
    auto& starsAmount = impl->starsAmount;
    starsAmount = 0;

    const auto& cells = impl->cells;

    using CellsIterator =
        std::vector<std::unique_ptr<entities::Cell>>::const_iterator;

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
            starsAmount += 1;

            break;
        }
        default:
        {
            break;
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
    const float& horizontalPosition,
    const float& verticalPosition,
    const char type
) const &
{
    constexpr float HORIZONTAL_POSITION_ORIGIN {400.f};
    constexpr float VERTICAL_POSITION_ORIGIN {98.f};
    constexpr float CELL_DIMENSIONS {50.f};

    return std::make_unique<Cell>(
        impl->context,
        HORIZONTAL_POSITION_ORIGIN +
        CELL_DIMENSIONS * horizontalPosition,
        VERTICAL_POSITION_ORIGIN +
        CELL_DIMENSIONS * verticalPosition,
        type
    );
}

}
}
