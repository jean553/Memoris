/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistdibute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distdibuted in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file GameContext.hpp
 * @brief context for cells and levels
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_GAME_CONTEXT
#define DEF_GAME_CONTEXT

namespace utils
{
class GameContext
{
public:

    /**
     * @brief constructor
     */
    GameContext();

    /**
     * @brief setter for the terminateGame attribute
     *
     * @param terminate true if the game must be terminated
     */
    void setTerminateGame(bool terminate);

    /**
     * @brief getter for the terminateGame attribute
     *
     * @return bool
     */
    bool getTerminateGame() const;

    /**
     * @brief setter for the star cells amount
     *
     * @param amount star cells quantity
     */
    void setStarCellsAmount(const uint16_t& amount);

    /**
     * @brief getter for the star cells amount
     *
     * @return uint16_t
     */
    uint16_t getStarCellsAmount() const;

    /**
     * @brief increment the amount of found star cells amount
     */
    void addFoundStarCell();

    /**
     * @brief getter for the found star cells amount
     *
     * @return uint16_t
     */
    uint16_t getFoundStarCellsAmount() const;

private:

    /* get by the game controller to stop the game, false by default */
    bool terminateGame;

    uint16_t starCellsAmount;
    uint16_t foundStarCellsAmount;
};
}

#endif
