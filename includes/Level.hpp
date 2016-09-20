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
 * @file Level.hpp
 * @brief level entity, contains all the cells
 * @package entities
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVEL_H_
#define MEMORIS_LEVEL_H_

#include "Cell.hpp"

#include "aliases.hpp"

#include <vector>
#include <memory>

namespace memoris
{
namespace entities
{

class Level
{

public:

    static constexpr unsigned short MIN_FLOOR {0};
    static constexpr unsigned short MAX_FLOOR {9};

    /**
     * @brief constructor, initialize all the cells of the level according to
     * the given level file path
     *
     * @param context reference to the current context
     * @param loadFromFile boolean false by default to indicate that the
     * level content has to be loaded from the next file in the serie
     * manager levels queue (false by default for safety). If the boolean is
     * false, the level is empty
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    Level(
        utils::Context& context,
        const bool loadFromFile = false
    );

    /**
     * @brief render the level and all the cells of the given floor; this
     * method is optimized and only calculate/render/display the cells of
     * the given floor; the other cells are totally ignored
     *
     * @param context reference to the current context to use
     * @param floor the floor to render
     * @param Cell object method pointer to the cell display() method to use
     */
    void display(
        utils::Context& context,
        const unsigned short& floor,
        void (Cell::*display)(
            utils::Context&,
            aliases::ConstTransformUniquePtrRef
        )
    ) const;

    /**
     * @brief hides all the cells of the level, call the method (hide()) for
     * all of them except for departure cell(s)
     *
     * @param context reference to the current context to use
     */
    void hideAllCellsExceptDeparture(
        utils::Context& context
    );

    /**
     * @brief update the transparency value of the current player color
     *
     * @param context reference to the current context
     * @param alpha the current player cell transparency value; we use a
     * sf::Uint8 value as this is the type used to set the colors of a
     * sf::Color object
     */
    void setPlayerCellTransparency(
        utils::Context& context,
        const sf::Uint8& alpha
    );

    /**
     * @brief move the player down if possible
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player
     * @param context reference to the current context to use
     */
    void movePlayer(
        utils::Context& context,
        const short& movement
    );

    /**
     * @brief check if the player is allowed to perform the given movement;
     * this function is called from the game controller each time the player
     * trigger an event to move on the level
     *
     * @param move the value (positive or negative) to apply on the current
     * player index; defines the mouvement of the player; this check is
     * separated into a dedicated method for better code organisation
     * @param floor the current player floor number
     *
     * @return bool
     */
    bool allowPlayerMovement(
        const short& movement,
        const unsigned short& floor
    ) const;

    /**
     * @brief get the current player cell type; this getter is used into the
     * game controller to execute the correct current player cell event action
     *
     * @return const char&
     */
    const char& getPlayerCellType() const;

    /**
     * @brief check if the expected cell after the movement is a wall cell,
     * if yes, show the wall cell and forbid the movement; this function is
     * called by the game controller when the player is allowed to move, we
     * check if the user is currently in collision with a wall; if there is
     * a collision, the wall is shown
     *
     * @param context reference to the current context
     * @param movement the movement direction, the same as movePlayer()
     *
     * @return bool
     */
    bool detectWalls(
        utils::Context& context,
        const short& movement
    ) const;

    /**
     * @brief updates the current player cell to an empty cell, whatever the
     * previous type; this method is called by the game controller to empty
     * a cell when the player leaves it; this method automatically forces the
     * load of a new texture for the player cell
     *
     * @param context reference to the current context
     */
    void emptyPlayerCell(
        utils::Context& context
    );

    /**
     * @brief moves the current player to the next floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the next floor
     *
     * @param context reference to the current context
     *
     * @bool true if the player moved to the next floor
     */
    bool movePlayerToNextFloor(utils::Context& context);

    /**
     * @brief moves the current player to the previous floor if possible,
     * returns true if the action has been executed, false if it is not
     * possible to move to the previous floor
     *
     * @param context reference to the current context to use
     *
     * @bool true if the player moved to the previous floor
     */
    bool movePlayerToPreviousFloor(
        utils::Context& context
    );

    /**
     * @brief getter of the total stars amount in the level; this is used by
     * the game controller to check when the user got all the stars of the
     * current played level
     *
     * @return const unsigned short&
     */
    const unsigned short& getStarsAmount();

    /**
     * @brief getter for the amount of playable floors; this is used to select
     * which floors have to be displayed during the watching period; this
     * amount is generated during the loading process of the level; it contains
     * the amount of floors (from the first one included) that contains at
     * least one non-empty cell
     *
     * @return const unsigned short&
     */
    const unsigned short& getPlayableFloors();

    /**
     * @brief getter for the current player floor index; we do not return
     * a reference because there is no attribute to store the player floor
     *
     * @return const unsigned short
     */
    const unsigned short getPlayerFloor();

    /**
     * @brief plays the floor transition animation; for now, the unique
     * animation renders a verical column that scroll the whole floor and
     * displays the next floor;
     *
     * @param context reference to the current context
     *
     * NOTE: this method must be called instead of 'display()' during the
     * animation
     */
    void playFloorTransitionAnimation(
        utils::Context& context
    );

    /**
     * @brief setter for the animation boolean
     *
     * @param animate true if the animation must be rendered; the animation
     * can be displayed using the method playFloorTransitionAnimation()
     */
    void setAnimateFloorTransition(const bool& animate);

    /**
     * @brief getter for the animation boolean
     *
     * @return const bool&
     */
    const bool& getAnimateFloorTransition();

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
     * @param context shared pointer to the context to use
     * @param transparency the value of SFML transparency
     * @param floor the concerned floor index
     */
    void setCellsTransparency(
        utils::Context& context,
        const float& transparency,
        const unsigned short& floor
    );

    /**
     * @brief getter of the cells container; returns a reference to the
     * container; we return a constant reference to the container; in that
     * case, the elements of the container cannot be modified (that means
     * each pointer into the container cannot be replaced by another one)
     * but the objects pointed by those pointers can be modified
     *
     * @return const std::vector<std::unique_ptr<Cell>>&
     */
    const std::vector<std::unique_ptr<Cell>>& getCells() const;

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
     * @param context current context
     * @param floor the current level floor displayed
     * @param type the type to apply on the 'mouse hover cell'
     *
     * @return const bool
     *
     * does not return a reference to a bool because the returned boolean is
     * a local variable of the method
     */
    const bool updateSelectedCellType(
        utils::Context& context,
        const unsigned short& floor,
        const char& type
    );

    /**
     * @brief refresh all the cells and reset them to empty cells
     *
     * @param context reference to the current context to use
     *
     * @throws std::terminate something wrong happened in the for_each
     * algorithm (functions that are called there may throw exceptions as
     * they are not declared noexcept)
     * @throws std::bad_alloc for_each algorithm failed to allocate memory
     *
     * context is not const because the method calls other functions that
     * modifies the SFML render window, which is a context attribute
     *
     * not 'const' because it modifies the cells inside the cells container
     *
     * not 'noexcept' because it could throw exceptions; those exceptions are
     * never caught and the program just stops if it happens
     */
    void refresh(utils::Context& context) &;

private:

    /**
     * @brief private method called by the constructor to load a level from
     * the next file in the serie manager queue
     *
     * @param context reference to the current context
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    void loadLevelFromFile(utils::Context& context);

    /**
     * @brief private method called by the constructor to load a level full
     * of empty cells
     *
     * @param context reference to the current context
     */
    void loadEmptyLevel(utils::Context& context);

    /**
     * @brief called by the constructor to update the cursor position during
     * the level creation
     */
    void updateCursors();

    /* container of unique pointers of cells; we use unique pointers because
       pointers are fast to copy/move instead of a whole cell object; we use
       a unique pointer to make the pointer as restrictif as possible, in fact,
       we only use dynamic allocation to make the program run faster, so this
       is always better to limit the freedom of variables */
    std::vector<std::unique_ptr<Cell>> cells;

    /* the index of the current player cell; the position of the player in
       the level; the variable is 0 by default; */
    unsigned short playerIndex {0};

    /* the total amount of stars on the level; the default amount is 0 before
       the level file is loaded */
    unsigned short starsAmount {0};

    /* contains the amount of floors that are playable in this level; a
       playable floor is a floor with at least one cell non empty; this is
       used to select which floor to display during the watching period */
    unsigned short playableFloors {0};

    /* the amount of minutes loaded from the file for the current level */
    unsigned short minutes {0};

    /* the amount of seconds loaded from the file for the current level */
    unsigned short seconds {0};

    /* this boolean is true when a switch level animation is currently playing;
       this boolean is used by the game controller to starts the floor switch
       animation but also to know when the animate has been terminated by the
       level (using setter and getter) */
    bool animateFloorTransition {false};

    /* this is a SFML unsigned integer used to store the last update time of
       the current level animation; this variable can be used for any kind
       of level animation as only one animation can occure at a time */
    sf::Uint32 lastAnimationTime {0};

    /* the following variables are used for level animation and effects */

    /* the current column index on which one the animation occures; for
       example, during a floor switch animation, each column is hidden one
       by one and the content of the next level progressively appears; this
       variable is used to store the current 'breaking' column of the effect */
    unsigned short animationColumn {0};

    /* the current floor index is stored inside this variable when the switch
       floor animation occures; this is used by the animation; */
    unsigned short animationFloor {0};

    /* we use an unique pointer here in order to load the transform and apply
       it on the cells rending process only when necessary (only when an
       animation that needs it is rendering); when the transform pointer is
       null, the transform is simply not applied */
    std::unique_ptr<sf::Transform> transform {nullptr};

    /* positions cursor used to keep trace of the initialized cell position
       when initializing every cell one by one */
    unsigned short horizontalPositionCursor {0}, verticalPositionCursor {0};

    /* boolean used to remember if one cell is at least non empty on the
       current loaded floor; used to increment the amount of playable floors */
    bool emptyFloor {true};

};

}
}

#endif
