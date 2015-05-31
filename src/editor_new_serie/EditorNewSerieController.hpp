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
 * Editor new serie screen.
 *
 * @file EditorNewSerieController.hpp
 * @brief new serie creation screen
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_NEW_SERIE_CONTROLLER 
#define DEF_EDITOR_NEW_SERIE_CONTROLLER 

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"

#include "../widgets/InputTextWidget.hpp"

#include "../defines/ColorsDefines.hpp"
#include "../defines/FontsDefines.hpp"

#define POSITION_NEW_SERIE_INPUT_TEXT_X 500
#define POSITION_NEW_SERIE_INPUT_TEXT_Y 300
#define POSITION_NEW_SERIE_EXPLANATION_X 570
#define POSITION_NEW_SERIE_EXPLANATION_Y 200

#define SIZE_NEW_SERIE_INPUT_TEXT 600

#define STRING_NEW_SERIE_DEFAULT ""
#define STRING_NEW_SERIE_EXPLANATION "New serie name"

#define MAX_NEW_SERIE_LENGTH 15

namespace controllers
{
    class EditorNewSerieController : public Controller
    {
        public:

            EditorNewSerieController();
            ~EditorNewSerieController();

            /**
             * @brief render the editor new serie screen
             *
             * @param Context context   commons items for controller
             *
             * @return char   id of the next screen controller
             */
            unsigned char render(
                utils::Context* context
            );


        private:

            sf::Font fontExplanation;

            sf::Color colorExplanation;

            sf::Text explanation;

            widgets::InputTextWidget *inputTextSerieName;
    };
}

#endif
