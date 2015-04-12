/**
 * @file main.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 *
 * Starting point of the program
 */

#include <SFML/Graphics.hpp>

#include "game/GameController.hpp"

/**
 * Main function of the program, load the window
 * and start all the program components
 *
 * @return EXIT_SUCCESS when the program correctly finish
 */
int main() 
{
    
    // create a window fullscreen and
    // force the resolution to 1600x900
    sf::RenderWindow *window = new sf::RenderWindow(
        sf::VideoMode(1600, 900, 32), 
        "SFML",
        sf::Style::Fullscreen
    );

    // create the main game controller
    // and run the application
    controllers::GameController game;
    game.run(window);

    return EXIT_SUCCESS;
}
