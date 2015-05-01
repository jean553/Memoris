/**
 * @file Controller.hpp
 * @brief parent class for all controllers
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN
#define DEF_SCREEN

#include <SFML/Graphics.hpp>

namespace controllers
{
    class Controller
    {
        public:

            Controller();
            ~Controller();

            /**
             * @brief render the screen, contains events catcher,
             *
             * @param RenderWindow window   the game main window
             */
            virtual void render(sf::RenderWindow* window) = 0;
    };
}

#endif
