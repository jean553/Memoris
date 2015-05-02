/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
