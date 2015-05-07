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
 * Common contents which can be
 * passed from one screen to another.
 *
 * @file Context.hpp
 * @brief common contents to be passed to controller
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_CONTEXT
#define DEF_CONTEXT

#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace utils
{
    class Context
    {
        public:

            Context();
            ~Context();

            /**
             * @brief common window setter
             *
             * @param RenderWindow common rendering window
             */
            void setWindow(sf::RenderWindow* commonWindow);

            /**
             * @brief common music setter
             *
             * @param Music commonMusic pointer to common music to use
             */
            void setMusic(sf::Music *commonMusic);

            /**
             * @bried message setter
             *
             * @param string message to send to next called controller
             */
            void setSentMessage(std::string message);

            /**
             * @brief common window getter
             *
             * @return common window pointer
             */
            sf::RenderWindow* getWindow();

            /**
             * @brief common music getter
             *
             * @return common music pointer
             */
            sf::Music* getMusic();

            /**
             * @brief common message getter
             *
             * @return common message string
             */
            std::string getSentMessage();

        private:

            sf::RenderWindow *window;

            sf::Music *music;

            std::string sentMessage;
    };
}

#endif
