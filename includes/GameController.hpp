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
 * @file GameController.hpp
 * @brief main game controller, renders the map and let the user play
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_GAMECONTROLLER_H_
#define MEMORIS_GAMECONTROLLER_H_

#include "Controller.hpp"

#include <memory>

namespace memoris
{

namespace entities
{
class Level;
}

namespace controllers
{

class GameController : public Controller
{
    using Level = std::shared_ptr<entities::Level>;

public:

    /**
     * @brief constructor, call the Level constructor that loads and create
     * the game level; initialize the watching time of the game
     *
     * @param context constant reference to the current context
     * @param levelPtr shared pointer to the level object to use
     * @param watchLevel indicates if there is a watching period or not (there
     * is no watching period if the level is started from the editor)
     *
     * @throw std::invalid_argument the level file cannot be opened
     */
    GameController(
        const utils::Context& context,
        const Level& levelPtr,
        const bool& watchLevel = true
    );

    /**
     * @brief default destructor, empty, only declared here in order to use
     * forwarding declaration
     */
    ~GameController() noexcept;

    /**
     * @brief renders the game main screen
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short& id of the new screen controller
     */
    virtual const unsigned short& render(
        const utils::Context& context
    ) & override final;

private:

    static constexpr float CELLS_DEFAULT_TRANSPARENCY {255.f};

    static constexpr unsigned short FIRST_FLOOR_INDEX {0};

    /* use the sf::Int32 type to avoid types conversions (this attribute is
       only used with sf::Int32 variables) */
    static constexpr sf::Int32 ONE_SECOND {1000};

    /**
     * @brief function that refectors all the management related to the player
     * movement; this action is called everytime the player makes a move on
     * the level; it checks if the movement is allowed, move the player on
     * the level and executes the player's new cell action
     *
     * @param context reference to the current context to use
     * @param the numeric representation of the movement's direction,
     * the delta between the current player cell and the destination cell
     *
     * NOTE: the user can only moves to the left, right, top or bottom; that's
     * why the only possible values here are -20, 20, -1 and 1. These values
     * are not checked when the function is executed.
     */
    void handlePlayerMovement(
        const utils::Context& context,
        const short& movement
    );

    /**
     * @brief applies the action of the new player cell; this method is called
     * immediately after the player moved
     *
     * @param context constant reference to the context to use
     */
    void executePlayerCellAction(const utils::Context& context);

    /**
     * @brief empties the player cell (the current player cell is switched to
     * an empty cell); this action is triggered everytime the player leaves
     * a cell; some types are never deleted from their original cell, this
     * function also checks that
     *
     * @param context shared pointer to the context to use
     */
    void emptyPlayerCell(const utils::Context& context);

    /**
     * @brief this method is called during the watching mode by the main
     * display method to jump to the next floor if the next floor is a playable
     * floor or to stop the watching period if there is no playable floor
     * anymore; this function is called at each 'watching time interval'
     *
     * @param context shared pointer to the context to use
     */
    void watchNextFloorOrHideLevel(const utils::Context& context);

    /**
     * @brief this method ends the level, it displays the win or lose screen
     * according if the player has just won or lost the current level
     *
     * @param context constant reference to the current context to use
     */
    void endLevel(const utils::Context& context);

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
