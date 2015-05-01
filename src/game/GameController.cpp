/**
 * @file GameController.hpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "GameController.hpp"

using namespace controllers;

/**
 *
 */
GameController::GameController()
{
    screenFactory = new factories::ScreenFactory();

    currentController = screenFactory->getScreenById(
        MAIN_MENU_CONTROLLER_ID
    );
}

/**
 *
 */
GameController::~GameController()
{
    delete screenFactory;

    delete currentController;
}

/**
 *
 */
void GameController::run(sf::RenderWindow* window)
{
    while(window->isOpen())
    {
        currentController->render(window);

        window->clear();

        window->display();
    }
}
