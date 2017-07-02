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
 * @brief level entity, contains all the cells
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
     */
    const bool isPlayerMovementAllowed(
        const sf::Event& event,
        const unsigned short& floor
    ) const &;

    /**
     * @brief render the level and all the cells of the given floor; this
     * method is optimized and only calculate/render/display the cells of
     * the given floor; the other cells are totally ignored
     *
     * @param floor the floor to render
     */
    void display(const unsigned short& floor) const;

    /**
     * @brief update the transparency value of the current player color
     *
     * @param alpha the current player cell transparency value; we use a
     * sf::Uint8 value as this is the type used to set the colors of a
     * sf::Color object
     */
    void setPlayerCellTransparency(const sf::Uint8& alpha);

    /**
     * @brief get the current player cell type; this getter is used into the
     * game controller to execute the correct current player cell event action
     *
     * @return const char&
     */
    const char& getPlayerCellType() const;

    /**
     * @brief updates the current player cell to an empty cell, whatever the
     * previous type; this method is called by the game controller to empty
     * a cell when the player leaves it; this method automatically forces the
     * load of a new texture for the player cell
     */
    void emptyPlayerCell();

    /**
     * @brief moves the current player to the next floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the next floor
     *
     * @bool true if the player moved to the next floor
     */
    bool canMovePlayerToNextFloor();

    /**
     * @brief moves the current player to the previous floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the previous floor
     *
     * @bool true if the player moved to the previous floor
     */
    bool canMovePlayerToPreviousFloor();

    /**
     * @brief getter of the total stars amount in the level; this is used by
     * the game controller to check when the user got all the stars of the
     * current played level
     *
     * @return const unsigned short&
     */
    const unsigned short& getStarsAmount();

    /**
     * @brief getter for the current player floor index; we do not return
     * a reference because there is no attribute to store the player floor
     *
     * @return const unsigned short
     */
    const unsigned short getPlayerFloor();

    /**
     * @brief getter for the minutes amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getMinutes() const;

    /**
     * @brief getter for the seconds amount loaded from the level file
     *
     * @return const unsigned short&
     */
    const unsigned short& getSeconds() const;

    /**
     * @brief getter of the player cell index
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayerCellIndex() const;

    /**
     * @brief setter of the player cell index
     *
     * @param index the value to set for the player cell index
     */
    void setPlayerCellIndex(const unsigned short& index);

    /**
     * @brief set the transparency of all the cells of the given floor
     *
     * @param transparency the value of SFML transparency
     * @param floor the concerned floor index
     */
    void setCellsTransparency(
        const float& transparency,
        const unsigned short& floor
    ) &;

    /**
     * @brief getter of the cells container; returns a reference to the
     * container; we return a constant reference to the container; in that
     * case, the elements of the container cannot be modified (that means
     * each pointer into the container cannot be replaced by another one)
     * but the objects pointed by those pointers can be modified
     *
     * @return const std::vector<std::unique_ptr<Cell>>&
     */
    const std::vector<std::unique_ptr<Cell>>& getCells() const & noexcept;

    /**
     * @brief dynamically create a SFML transform object pointed by the
     * 'transform' pointer, member of this class
     */
    void createTransform();

    /**
     * @brief dynamically delete the SFML transform object pointed by the
     * 'transform' pointer, member of this class
     */
    void deleteTransform();

    /**
     * @brief rotate all the cells with the given amount of degrees; the
     * center of the rotation is the level floor center
     *
     * @param degrees amount of degrees for the rotation
     *
     * NOTE: the function createTransform() has to be called AFTER the
     * dynamic creation of a SFML transform object (createTransform()).
     */
    void rotateAllCells(const short& degrees);

    /**
     * @brief check if the mouse is hover a cell on the current floor of the
     * the level and replace it with the given type; returns a boolean that
     * indicates if the level has been modified or not
     *
     * @param floor the current level floor displayed
     * @param type the type to apply on the 'mouse hover cell'
     *
     * @return const bool
     *
     * does not return a reference to a bool because the returned boolean is
     * a local variable of the method
     */
    const bool updateSelectedCellType(
        const unsigned short& floor,
        const char& type
    );

    /**
     * @brief refresh all the cells and reset them to wall cells
     *
     * @throws std::terminate something wrong happened in the for_each
     * algorithm (functions that are called there may throw exceptions as
     * they are not declared noexcept)
     * @throws std::bad_alloc for_each algorithm failed to allocate memory
     *
     * not 'const' because it modifies the cells inside the cells container
     *
     * not 'noexcept' because it could throw exceptions; those exceptions are
     * never caught and the program just stops if it happens
     */
    void refresh() &;

    /**
     * @brief show all the cells (this is used by the level editor, just
     * after a level has been tested; in fact, the level object is the same,
     * so some cells have been hidden during the game)
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
     * @brief set the player on the departure cell if it exists; counts the
     * total amount of stars on the level; this method is used by the game
     * controller in order to initialize a level that is edited
     */
    void initializeEditedLevel() const & noexcept;

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
     * @brief called by the constructor to update the cursor position during
     * the level creation
     */
    void updateCursors() const & noexcept;

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
