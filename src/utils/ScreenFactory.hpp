/**
 * Factory which generates the screens.
 *
 * @file ScreenFactory.hpp
 * @brief factory to generate the game screens
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCREEN_FACTORY
#define DEF_SCREEN_FACTORY

#include "Controller.hpp"

#include "../main_menu/MainMenuController.hpp"

namespace factories
{
    class ScreenFactory
    {
        public:

            ScreenFactory();
            ~ScreenFactory();

            /**
             * @brief returns a new controller
             * pointer according to the given
             * screen id, used for screens
             * generation and screens switching.
             *
             * @param char id   id of the screen
             *
             * @return screen controller pointer,
             * returns null if no screen match
             */
            controllers::Controller* getScreenById(unsigned char id);
    };
}

#endif
