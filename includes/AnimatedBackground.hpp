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
 * @brief manage the menu background animation
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ANIMATEDBACKGROUND_H_
#define MEMORIS_ANIMATEDBACKGROUND_H_

#include "NotCopiable.hpp"
#include "Cell.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace memoris
{
namespace utils
{

class AnimatedBackground : public others::NotCopiable
{
public:

    /**
     * @brief public class method used to get the unique singleton animated
     * background instance; in fact, the animated background is generated
     * one time and it the same for all the menus
     *
     * @return static AnimatedBackground&
     */
    static AnimatedBackground& get();

    /**
     * @brief render the animated background, display all the cells
     */
    void render();

private:

    /**
     * @brief constructor, does nothin except calling the function to
     * initialize the cells of the background
     */
    AnimatedBackground();

    /**
     * @brief initialize all the cells of the animated background; this
     * method is the unique function that is called by the animated background
     * constructor; the creation of the cells could be done directly into
     * the constructor, but I prefer separate it into a dedicated function, as
     * this method requires a lot of internal variables
     */
    void initializeCells();

    /* the array of displayed cells in the background; this is an array of
       18 rows and 32 columns, that means 576 cells; we declare the cells
       one by one in the creation cells loop; we store simple Cells objects
       and not pointers; in fact, the cells are created one by one in the loop
       and copied into the container; they never change after */
    std::vector<entities::Cell> cells;
};

}
}

#endif
