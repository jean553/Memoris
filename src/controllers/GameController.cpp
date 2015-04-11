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
    mainMenuController = new MainMenuController();
}

/**
 *
 */
GameController::~GameController()
{
    delete mainMenuController;
}

/**
 *
 */
void GameController::run(sf::RenderWindow* window)
{
    // main program loop
    while(window->isOpen())
    {

        // TODO: event catch procedure must
        // be located inside a screen object
        // and not directly inside the game loop

        sf::Event event;

        // render game and catch events
        while(window->pollEvent(event))
        {
            switch(event.type)
            {
                // action when a key is pressed
                case sf::Event::KeyPressed:
                {
                    switch(event.key.code)
                    {
                        // terminate the program when
                        // escape button is pressed
                        case sf::Keyboard::Escape:
                        {
                            window->close();
                            break;
                        }
                    }
                }
            }
        }

        // clear the window in black color
        window->clear();

        // display the whole window content
        window->display();
    }
}
