/**
 * @file MainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MainMenuController.hpp"

using namespace controllers;

/**
 *
 */
MainMenuController::MainMenuController() {
}

/**
 *
 */
MainMenuController::~MainMenuController() {
}

/**
 *
 */
void MainMenuController::render(sf::RenderWindow* window) {

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
}
