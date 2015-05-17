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

#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"

#include "../widgets/InputTextWidget.hpp"

#include "../defines/ColorsDefines.hpp"
#include "../defines/FontsDefines.hpp"

#define STRING_NEW_GAME_TITLE "New game"
#define STRING_NEW_GAME_EXPLANATION "Your name :"
#define STRING_NAME_DEFAULT ""

#define SIZE_NEW_GAME_TITLE_FONT 70
#define SIZE_NEW_GAME_EXPLANATION_FONT 50
#define SIZE_NAME_INPUT_TEXT 600

#define POSITION_NEW_GAME_TITLE_X 620
#define POSITION_NEW_GAME_TITLE_Y 200
#define POSITION_NEW_GAME_EXPLANATION_X 645
#define POSITION_NEW_GAME_EXPLANATION_Y 380
#define POSITION_NAME_INPUT_TEXT_X 500
#define POSITION_NAME_INPUT_TEXT_Y 450

#define MAX_NAME_LENGTH 15

namespace controllers
{
    class NewGameController : public Controller
    {
        public:

            NewGameController();
            ~NewGameController();

            /**
             * @brief render the new game screen
             *
             * @param Context context   commons items for controller
             *
             * @return char   id of the next screen controller
             */
            unsigned char render(
                utils::Context* context
            );

        private:

            sf::Font fontTitle;
            sf::Font fontExplanation;

            sf::Color colorTitle;
            sf::Color colorExplanation;

            sf::Text title;
            sf::Text explanation;

            widgets::InputTextWidget *inputTextGameName;
    };
}

#endif
