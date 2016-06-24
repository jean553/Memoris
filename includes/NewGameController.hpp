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
 * New game screen.
 *
 * @file NewGameController.hpp
 * @brief new game screen of the program
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_NEW_GAME
#define DEF_NEW_GAME

#include <SFML/Graphics.hpp>

#include "Controller.hpp"

#include "InputTextWidget.hpp"

namespace memoris
{
namespace controllers
{

class NewGameController : public Controller
{

    static const std::string STRING_NEW_GAME_TITLE;
    static const std::string STRING_NEW_GAME_EXPLANATION;
    static const std::string STRING_NAME_DEFAULT;

    static const unsigned short SIZE_NAME_INPUT_TEXT;

    static const unsigned short POSITION_NEW_GAME_TITLE_X;
    static const unsigned short POSITION_NEW_GAME_TITLE_Y;

    static const unsigned short POSITION_NEW_GAME_EXPLANATION_X;
    static const unsigned short POSITION_NEW_GAME_EXPLANATION_Y;

    static const unsigned short POSITION_NAME_INPUT_TEXT_X;
    static const unsigned short POSITION_NAME_INPUT_TEXT_Y;

    static const unsigned short MAX_NAME_LENGTH;

public:

    NewGameController(utils::Context& context);

    /**
     * @brief render the new game screen
     *
     * @param context commons items for controller
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render(utils::Context& context);

private:

    sf::Text title;
    sf::Text explanation;

    widgets::InputTextWidget inputTextGameName;
};

}
}

#endif
