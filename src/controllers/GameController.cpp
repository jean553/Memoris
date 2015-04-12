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
    mainMenuScreen = new controllers::MainMenuScreen();
}

/**
 *
 */
GameController::~GameController()
{
    delete mainMenuScreen;
}

/**
 *
 */
void GameController::run(sf::RenderWindow* window)
{
    // main program loop
    while(window->isOpen())
    {
        // TODO: use a parent class 'Screen'
        // with an abstract method render()
        // which returns another Screen type
        // object for the next screen which
        // must be displayed
        mainMenuScreen->render(window);

        // clear the window in black color
        window->clear();

        // display the whole window content
        window->display();
    }
}
