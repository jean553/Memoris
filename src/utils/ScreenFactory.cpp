/**
 * @file ScreenFactory.hpp
 * @package factories
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "ScreenFactory.hpp"

using namespace factories;

/**
 *
 */
ScreenFactory::ScreenFactory()
{
}

/**
 *
 */
ScreenFactory::~ScreenFactory()
{
}

/**
 *
 */
controllers::Controller* ScreenFactory::getScreenById(
    unsigned char id
) {

    switch(id)
    {
        case 1:
            return new controllers::MainMenuController;
        default:
            return NULL;
    }
}
