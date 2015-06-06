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

#include "../defines/SoundsDefines.hpp"

#define STRING_EDITOR_SERIE_TITLE "Serie editor"

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

            sf::SoundBuffer soundBuffer;

            sf::Sound soundOpenScreen;
    };
}

#endif
