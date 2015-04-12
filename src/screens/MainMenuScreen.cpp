/**
 * @file MainMenuScreen.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MainMenuScreen.hpp"

using namespace controllers;

/**
 *
 */
MainMenuScreen::MainMenuScreen() : Screen() {
}

/**
 *
 */
MainMenuScreen::~MainMenuScreen() {
}

/**
 *
 */
void MainMenuScreen::render(sf::RenderWindow* window) {

    // TODO: check to refactor the event object
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
