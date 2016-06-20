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
 * @file AnimatedBackground.hpp
 * @brief background animation
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_ANIMATED_BACKGROUND
#define DEF_ANIMATED_BACKGROUND

#include <SFML/Graphics.hpp>
#include <vector>

#include "Context.hpp"
#include "Cell.hpp"

namespace utils
{
class AnimatedBackground
{
public:

    /**
     * @brief constructor
     *
     * @param context current context reference
     */
    AnimatedBackground(utils::Context& context);

    /**
     * @brief animate the background
     *
     * @param context pointer to the current context
     */
    void animate(utils::Context& context);

private:

    static const uint16_t TOTAL_CELLS_AMNT;

    static const uint8_t RANDOM_MAX;
    static const uint8_t COLS_AMNT;
    static const uint8_t LINES_AMNT;
    static const uint8_t ANIMATION_INTERVAL;

    static const int8_t CELL_ORIGINAL_HRTL_PSTN;

    /**
     * @brief initialize the cells array randomly
     *
     * @param context current context reference
     */
    void initializeCells(utils::Context& context);

    /**
     * @brief initialize the cells lib array
     */
    void initializeCellsLib();

    std::vector<entities::Cell> cells;

    /* as the cells are randomly selected, a number must be attached */
    std::vector<std::string> cellsLib;

    sf::Clock clock;
};
}

#endif
