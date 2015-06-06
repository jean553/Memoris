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
 * Serie editor main screen.
 *
 * @file EditorSerieController.hpp
 * @brief serie editor screen
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_SERIE_CONTROLLER
#define DEF_EDITOR_SERIE_CONTROLLER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"

#include "../widgets/TitleBarWidget.hpp"
#include "../widgets/ButtonWidget.hpp"

#include "../defines/SoundsDefines.hpp"

#define STRING_EDITOR_SERIE_TITLE "Serie editor"

#define EDITOR_SERIE_BUTTON_NEW_POSITION_X 10
#define EDITOR_SERIE_BUTTON_OPEN_POSITION_X 240
#define EDITOR_SERIE_BUTTON_SAVE_POSITION_X 470
#define EDITOR_SERIE_BUTTON_ADD_POSITION_X 700
#define EDITOR_SERIE_BUTTON_EXIT_POSITION_X 1390

#define EDITOR_SERIE_BUTTON_NEW_TEXT "New"
#define EDITOR_SERIE_BUTTON_OPEN_TEXT "Open"
#define EDITOR_SERIE_BUTTON_SAVE_TEXT "Save"
#define EDITOR_SERIE_BUTTON_ADD_TEXT "Add"
#define EDITOR_SERIE_BUTTON_EXIT_TEXT "Exit"

#define EDITOR_SERIE_BUTTONS_POSITION_Y 100
#define EDITOR_SERIE_BUTTONS_WIDTH 200

namespace controllers
{
    class EditorSerieController : public Controller
    {
        public:

            EditorSerieController();
            ~EditorSerieController();

            /**
             * @brief render the serie editor screen
             *
             * @param Context context   commons items for controller
             *
             * @return char   id of the next screen controller
             */
            unsigned char render(
                utils::Context* context
            );

        private:

            widgets::TitleBarWidget *titleBar;

            widgets::ButtonWidget *buttonNew;
            widgets::ButtonWidget *buttonOpen;
            widgets::ButtonWidget *buttonSave;
            widgets::ButtonWidget *buttonAdd;
            widgets::ButtonWidget *buttonExit;

            sf::SoundBuffer soundBuffer;

            sf::Sound soundOpenScreen;
    };
}

#endif
