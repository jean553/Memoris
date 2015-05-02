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
    fontTitle.loadFromFile(PATH_FONT_TITLE);
    fontItem.loadFromFile(PATH_FONT_ITEM);

    colorTitle.r = COLOR_TITLE_RED_INIT;
    colorTitle.g = COLOR_TITLE_GREEN_INIT;
    colorTitle.b = COLOR_TITLE_BLUE_INIT;
    colorTitle.a = COLOR_TITLE_ALPHA;

    colorWhite.r = COLOR_WHITE_RED;
    colorWhite.g = COLOR_WHITE_GREEN;
    colorWhite.b = COLOR_WHITE_BLUE;
    colorWhite.a = COLOR_WHITE_ALPHA;

    title.setFont(fontTitle);
    title.setString(STRING_TITLE);
    title.setCharacterSize(SIZE_TITLE_FONT);
    title.setColor(colorTitle);
    title.setPosition(POSITION_TITLE_X, POSITION_TITLE_Y);

    itemNewGame.setFont(fontItem);
    itemNewGame.setString(STRING_NEW_GAME);
    itemNewGame.setCharacterSize(SIZE_ITEM_FONT);
    itemNewGame.setColor(colorWhite);
    itemNewGame.setPosition(
        POSITION_ITEM_NEW_GAME_X,
        POSITION_ITEM_NEW_GAME_Y
    );

    itemLoadGame.setFont(fontItem);
    itemLoadGame.setString(STRING_LOAD_GAME);
    itemLoadGame.setCharacterSize(SIZE_ITEM_FONT);
    itemLoadGame.setColor(colorWhite);
    itemLoadGame.setPosition(
        POSITION_ITEM_LOAD_GAME_X,
        POSITION_ITEM_LOAD_GAME_Y
    );

    itemEditor.setFont(fontItem);
    itemEditor.setString(STRING_EDITOR);
    itemEditor.setCharacterSize(SIZE_ITEM_FONT);
    itemEditor.setColor(colorWhite);
    itemEditor.setPosition(
        POSITION_ITEM_EDITOR_X,
        POSITION_ITEM_EDITOR_Y
    );

    itemOptions.setFont(fontItem);
    itemOptions.setString(STRING_OPTIONS);
    itemOptions.setCharacterSize(SIZE_ITEM_FONT);
    itemOptions.setColor(colorWhite);
    itemOptions.setPosition(
        POSITION_ITEM_OPTIONS_X,
        POSITION_ITEM_OPTIONS_Y
    );

    itemExit.setFont(fontItem);
    itemExit.setString(STRING_EXIT);
    itemExit.setCharacterSize(SIZE_ITEM_FONT);
    itemExit.setColor(colorWhite);
    itemExit.setPosition(
        POSITION_ITEM_EXIT_X,
        POSITION_ITEM_EXIT_Y
    );

    textureGithub.loadFromFile(PATH_IMAGE_GITHUB);

    spriteGithub.setTexture(textureGithub, true);
    spriteGithub.setPosition(
        POSITION_GITHUB_X,
        POSITION_GITHUB_Y
    );

    musicMainMenu.openFromFile(PATH_MUSIC_MAIN_MENU);

    titleRedDirection = DIRECTION_TITLE_RED_INIT;
    titleGreenDirection = DIRECTION_TITLE_GREEN_INIT;
    titleBlueDirection = DIRECTION_TITLE_BLUE_INIT;

    //TODO: not an initialization function,
    //check if it can be moved in the rendering
    musicMainMenu.play();
}

/**
 *
 */
MainMenuController::~MainMenuController()
{
    musicMainMenu.stop();
}

/**
 *
 */
void MainMenuController::render(sf::RenderWindow* window)
{
    // animate the items
    if(clock.getElapsedTime().asMilliseconds() >
        INTERVAL_ANIMATION_TITLE
    ) {

        animateTitleColor();

        clock.restart();
    }

    window->draw(title);
    window->draw(itemNewGame);
    window->draw(itemLoadGame);
    window->draw(itemEditor);
    window->draw(itemOptions);
    window->draw(itemExit);
    window->draw(spriteGithub);

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

/**
 *
 */
void MainMenuController::animateTitleColor()
{
    // update color values
    colorTitle.r += titleRedDirection;
    colorTitle.g += titleGreenDirection;
    colorTitle.b += titleBlueDirection;

    // switch colors updates directions
    if(colorTitle.r == COLOR_TITLE_RED_MAX ||
       colorTitle.r == COLOR_TITLE_ALL_MIN
    ) {
        titleRedDirection = -titleRedDirection;
    }

    if(colorTitle.g == COLOR_TITLE_GREEN_MAX ||
       colorTitle.g == COLOR_TITLE_ALL_MIN
    ) {
        titleGreenDirection = -titleGreenDirection;
    }

    if(colorTitle.b == COLOR_TITLE_BLUE_MAX ||
    colorTitle.b == COLOR_TITLE_ALL_MIN
    ) {
        titleBlueDirection = -titleBlueDirection;
    }

    title.setColor(colorTitle);
}
