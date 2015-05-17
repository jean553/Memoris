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
 * Editor main menu screen.
 *
 * @file EditorMainMenuController.hpp
 * @brief main menu of the editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_MAIN_MENU_CONTROLLER
#define DEF_EDITOR_MAIN_MENU_CONTROLLER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../utils/Controller.hpp"
#include "../utils/Context.hpp"

#include "../defines/ColorsDefines.hpp"
#include "../defines/FontsDefines.hpp"
#include "../defines/SoundsDefines.hpp"

#define STRING_EDITOR "Editor"
#define STRING_NEW_SERIE "New"
#define STRING_OPEN_SERIE "Open"

#define POSITION_EDITOR_TITLE_X 690
#define POSITION_EDITOR_TITLE_Y 200
#define POSITION_ITEM_EDITOR_NEW_SERIE_X 720
#define POSITION_ITEM_EDITOR_NEW_SERIE_Y 400
#define POSITION_ITEM_EDITOR_OPEN_SERIE_X 710
#define POSITION_ITEM_EDITOR_OPEN_SERIE_Y 500

#define EDITOR_MENU_ITEM_NEW_SERIE 0
#define EDITOR_MENU_ITEM_OPEN_SERIE 1

#define EDITOR_MAIN_MENU_SELECTOR_MAX 1
#define EDITOR_MAIN_MENU_SELECTOR_MIN 0

namespace controllers
{
    class EditorMainMenuController : public Controller
    {
        public:

            EditorMainMenuController();
            ~EditorMainMenuController();

            /**
             * @brief render the editor main menu
             *
             * @param Context context   commons items for controller
             *
             * @return char   id of the next screen controller
             */
            unsigned char render(
                utils::Context* context
            );

        private:

            unsigned char selectorPosition;

            sf::Font fontTitle;
            sf::Font fontItem;

            sf::Color colorTitle;
            sf::Color colorWhite;
            sf::Color colorRed;

            sf::Text titleEditor;
            sf::Text itemNewSerie;
            sf::Text itemOpenSerie;

            sf::SoundBuffer soundBufferMove;
            sf::SoundBuffer soundBufferSelect;

            sf::Sound soundSelectorMove;
            sf::Sound soundSelectorSelect;

            /**
             * @brief update the menu selector position
             */
            void updateSelectorPosition();

            /**
             * @brief execute action according to
             * the selected menu item
             *
             * @param RenderWindow window main window
             */
            void selectMenuItem(sf::RenderWindow* window);
    };
}

#endif
