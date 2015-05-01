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
MainMenuController::MainMenuController() : Controller()
{
    sf::Color colorBlue(0, 0, 225, 255);

    fontTitle.loadFromFile("res/fonts/designer_block.ttf");

    title.setFont(fontTitle);
    title.setString("Memoris");
    title.setCharacterSize(TITLE_FONT_SIZE);
    title.setColor(colorBlue);
    title.setPosition(640,100);
}

/**
 *
 */
MainMenuController::~MainMenuController()
{
}

/**
 *
 */
void MainMenuController::render(sf::RenderWindow* window)
{
    window->draw(title);

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
