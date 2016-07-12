/**
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
 * @file NewGameController.hpp
 * @brief controller that displays the new game screen; this screen contains
 * a title and an input text widget to let the user enter the name of the
 * new game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_NEWGAME_H_
#define MEMORIS_NEWGAME_H_

#include "Controller.hpp"

#include <SFML/Graphics.hpp>

#include "InputTextWidget.hpp"

namespace memoris
{
namespace controllers
{

class NewGameController : public Controller
{

public:

    /**
     * @brief constructor, creates the title surface and the explanation
     * label surface; creates the input text widget
     */
    NewGameController();

    /**
     * @brief render the new game screen
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render();

private:

    /* the new game screen title */
    sf::Text title;

    /* the new game screen short explanation indicating the text input widget
       is used to specify the name of the game */
    sf::Text explanation;

    /* the input text widget is used to let the user enter the name of the
       new game to create */
    widgets::InputTextWidget inputTextGameName;
};

}
}

#endif
