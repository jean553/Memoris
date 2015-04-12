/**
 * Parent class for Screen type.
 *
 * @file Screen.hpp
 * @brief parent class for Screen type
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN
#define DEF_SCREEN

#include <SFML/Graphics.hpp>

namespace controllers
{
    class Screen
    {
        public:

            Screen();
            ~Screen();

        protected:

            /**
             * @brief render the screen, contains events catcher,
             *
             * @param RenderWindow window   the game main window
             */
            virtual void render(sf::RenderWindow* window) = 0;
    };
}

#endif
