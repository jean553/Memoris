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
 * @file Level.hpp
 * @brief manages the level
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVEL_H_
#define MEMORIS_LEVEL_H_

#include <memory>
#include <vector>

namespace sf
{
class Transform;
class Event;

/* 'typedef unsigned char Uint8' in SFML/Config.hpp, we declare exactly
   the same type here in order to both use declaration forwarding and
   prevent conflicting declaration */
typedef unsigned char Uint8;
}

namespace memoris
{

namespace entities
{
class Cell;
}

namespace utils
{
class Context;
}

namespace entities
{

class Level
{

public:

    /**
     * @brief constructor that creates a blank level (level editor)
     *
     * @param context the context to use

     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    Level(const utils::Context& context);

    /**
     * @brief constructor that creates a level from a level file (game)
     *
     * @param context the context to use
     * @param filePath the level file to load (full path)
     *
     * @throw std::invalid_argument the level file cannot be opened;
     * this exception is caught into the controllers factory
     * and display an error message to the screen
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    Level(
        const utils::Context& context,
        const std::string& filePath
    );

    /**
     * @brief default destructor
     */
    ~Level();

    /**
     * @brief returns the floor index with the last cell on it (not a wall one)
     *
     * @return const unsigned short
     */
    const unsigned short getLastPlayableFloor() const & noexcept;

    /**
     * @brief marks the player cell as visible and shows it
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void showPlayerCell() const &;

    /**
     * @brief hides all the cells of the level
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void hideAllCells() const &;

    /**
     * @brief updates the player position to the top cell
     */
    void makeTopMovement() const & noexcept;

    /**
     * @brief updates the player position to the bottom cell
     */
    void makeBottomMovement() const & noexcept;

    /**
     * @brief updates the player position to the left cell
     */
    void makeLeftMovement() const & noexcept;

    /**
     * @brief updates the player position to the right cell
     */
    void makeRightMovement() const & noexcept;

    /**
     * @brief returns the position (both horizontal and vertical)
     * of the current player cell
     *
     * @return const std::pair<float, float>
     */
    const std::pair<float, float> getPlayerPosition() const & noexcept;

    /**
     * @brief checks if the player is allowed to go in the expected direction
     * (does not leave the level or colide with a wall)
     *
     * @param event the current event, contains the expected direction
     * @param floor the current displayed floor
     *
     * @return const bool
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    const bool isPlayerMovementAllowed(
        const sf::Event& event,
        const unsigned short& floor
    ) const &;

    /**
     * @brief render all the cells of the given floor
     *
     * @param floor the floor to render
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void display(const unsigned short& floor) const &;

    /**
     * @brief update the transparency value of the current player cell
     *
     * @param alpha the player cell transparency to set
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void setPlayerCellTransparency(const sf::Uint8& alpha) const &;

    /**
     * @brief get the current player cell type
     *
     * @return const char&
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    const char& getPlayerCellType() const &;

    /**
     * @brief updates the current player cell to an empty cell;
     * used when the player leaves a cell
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void emptyPlayerCell() const &;

    /**
     * @brief getter of the total stars amount in the level
     *
     * @return const unsigned short&
     */
    const unsigned short& getStarsAmount() const & noexcept;

    /**
     * @brief getter for the current player floor index
     *
     * @return const unsigned short
     */
    const unsigned short getPlayerFloor() const & noexcept;

    /**
     * @brief getter for the minutes amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getMinutes() const & noexcept;

    /**
     * @brief getter for the seconds amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getSeconds() const & noexcept;

    /**
     * @brief getter of the player cell index
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayerCellIndex() const & noexcept;

    /**
     * @brief setter of the player cell index
     *
     * @param index the value to set for the player cell index
     */
    void setPlayerCellIndex(const unsigned short& index) const & noexcept;

    /**
     * @brief set the transparency of all the cells of the given floor
     *
     * @param transparency the value of SFML transparency
     * @param floor the concerned floor index
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void setCellsTransparency(
        const float& transparency,
        const unsigned short& floor
    ) const &;

    /**
     * @brief getter of the cells container;
     *
     * NOTE: we return a constant reference to the container; in that
     * case, the elements of the container cannot be modified (that means
     * each pointer into the container cannot be replaced by another one)
     * but the objects pointed by those pointers can be modified;
     * this function is used by animations that modify cells disposition
     *
     * @return const std::vector<std::unique_ptr<Cell>>&
     */
    const std::vector<std::unique_ptr<Cell>>& getCells() const & noexcept;

    /**
     * @brief dynamically creates a SFML Tranform object
     *
     * TODO: #1261 transform seems useless, check if it is really necessary
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void createTransform() const &;

    /**
     * @brief dynamically delete the SFML transform object
     *
     * TODO: #1261 transform seems useless, check if it is really necessary
     */
    void deleteTransform() const & noexcept;

    /**
     * @brief rotate all the cells with the given amount of degrees
     *
     * @param degrees amount of degrees for the rotation
     *
     * NOTE: the function createTransform() has to be called AFTER the
     * dynamic creation of a SFML transform object (createTransform()).
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void rotateAllCells(const short& degrees) const &;

    /**
     * @brief checks if the mouse is hover a cell on the current floor and
     * replaces it with the given type; returns a boolean that
     * indicates if the level has been modified or not
     *
     * @param floor the current level floor displayed
     * @param type the type to apply on the 'mouse hover' cell
     *
     * @return const bool
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    const bool updateSelectedCellType(
        const unsigned short& floor,
        const char& type
    ) const &;

    /**
     * @brief reset all cells to wall cells
     *
     * @throws std::terminate something wrong happened in the for_each
     * algorithm (functions that are called there may throw exceptions as
     * they are not declared noexcept)
     *
     * @throws std::bad_alloc for_each algorithm failed to allocate memory
     */
    void allCellsAsWalls() const &;

    /**
     * @brief show all the cells of the level
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void showAllCells() const &;

    /**
     * @brief checks if the level has exactly one departure and one arrival;
     * this method is used to check if the level can be tested in the
     * level editor
     *
     * @return const bool
     *
     * the returned value is directly created into the method
     */
    const bool hasOneDepartureAndOneArrival() const & noexcept;

    /**
     * @brief set the player on the departure cell if it exists;
     * counts the amount of stars on the whole level and saves it
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void initializeEditedLevel() const &;

    /**
     * @brief creates and returns an array of characters representing the level
     *
     * @return const std::vector<char>
     *
     * the returned value is directly created into the method, so the function
     * does not return a reference
     */
    const std::vector<char> getCharactersList() const & noexcept;

    /**
     * @brief update the cells of the level according to a given list
     * of characters
     *
     * @param characters array of characters
     */
    void setCellsFromCharactersList(const std::vector<char>& characters)
        const &;

private:

    /**
     * @brief increment the column index including the row index
     * if the column index gets its maximum value
     *
     * @param row the row to increment
     * @param column the column to increment
     */
    void incrementRowAndColumnIndexes(
        unsigned short& row,
        unsigned short& column
    ) const & noexcept;

    /**
     * @brief returns a pointer to the created cell according to the given type
     *
     * @param horizontalPosition cell horizontal position
     * @param verticalPosition cell vertical position
     * @param type cell type
     *
     * @return std::unique_ptr<Cell>
     *
     * @throw std::bad_alloc the pointer cannot be initialized;
     * the exception is never caught and the program stops
     */
    std::unique_ptr<Cell> getCellByType(
        const float& horizontalPosition,
        const float& verticalPosition,
        const char type
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
