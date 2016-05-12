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
 * @file GameContext.cpp
 * @brief context for cells and levels
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

using namespace utils;

/**
 *
 */
GameContext::GameContext()
{
    terminateGame = false;

    starCellsAmount = 0;
    foundStarCellsAmount = 0;
}

/**
 *
 */
void GameContext::setTerminateGame(bool terminate)
{
    terminateGame = terminate;
}

/**
 *
 */
bool GameContext::getTerminateGame() const
{
    return terminateGame;
}

/**
 *
 */
void GameContext::setStarCellsAmount(const uint16_t& amount)
{
    starCellsAmount = amount;
}

/**
 *
 */
uint16_t GameContext::getStarCellsAmount() const
{
    return starCellsAmount;
}

/**
 *
 */
void GameContext::addFoundStarCell()
{
    foundStarCellsAmount += 1;
}

/**
 *
 */
uint16_t GameContext::getFoundStarCellsAmount() const
{
    return foundStarCellsAmount;
}
