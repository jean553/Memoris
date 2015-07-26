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

const std::string MainMenuController::PATH_IMAGE_GITHUB = "res/images/fork-me.png";
const std::string MainMenuController::STRING_TITLE = "Memoris";
const std::string MainMenuController::STRING_NEW_GAME = "New game";
const std::string MainMenuController::STRING_LOAD_GAME = "Load game";
const std::string MainMenuController::STRING_EDITOR = "Editor";
const std::string MainMenuController::STRING_OPTIONS = "Options";
const std::string MainMenuController::STRING_EXIT = "Exit";

/**
 *
 */
MainMenuController::MainMenuController() : Controller()
{
    fontTitle.loadFromFile(constants::Fonts::getTitleFontPath());
    fontItem.loadFromFile(constants::Fonts::getTextFontPath());

    colorTitle.r = COLOR_TITLE_RED_INIT;
    colorTitle.g = COLOR_TITLE_GREEN_INIT;
    colorTitle.b = COLOR_TITLE_BLUE_INIT;
    colorTitle.a = constants::Colors::COLOR_ALPHA_FULL;

    colorWhite.r = constants::Colors::COLOR_WHITE_RED;
    colorWhite.g = constants::Colors::COLOR_WHITE_GREEN;
    colorWhite.b = constants::Colors::COLOR_WHITE_BLUE;
    colorWhite.a = constants::Colors::COLOR_ALPHA_FULL;

    colorRed.r = constants::Colors::COLOR_RED_RED;
    colorRed.g = constants::Colors::COLOR_RED_GREEN;
    colorRed.b = constants::Colors::COLOR_RED_BLUE;
    colorRed.a = constants::Colors::COLOR_ALPHA_FULL;

    title.setFont(fontTitle);
    title.setString(STRING_TITLE);
    title.setCharacterSize(constants::Fonts::SIZE_TITLE_FONT);
    title.setColor(colorTitle);
    title.setPosition(
        POSITION_TITLE_X,
        POSITION_TITLE_Y
    );

    itemNewGame.setFont(fontItem);
    itemNewGame.setString(STRING_NEW_GAME);
    itemNewGame.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemNewGame.setColor(colorRed);
    itemNewGame.setPosition(
        POSITION_ITEM_NEW_GAME_X,
        POSITION_ITEM_NEW_GAME_Y
    );

    itemLoadGame.setFont(fontItem);
    itemLoadGame.setString(STRING_LOAD_GAME);
    itemLoadGame.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemLoadGame.setColor(colorWhite);
    itemLoadGame.setPosition(
        POSITION_ITEM_LOAD_GAME_X,
        POSITION_ITEM_LOAD_GAME_Y
    );

    itemEditor.setFont(fontItem);
    itemEditor.setString(STRING_EDITOR);
    itemEditor.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemEditor.setColor(colorWhite);
    itemEditor.setPosition(
        POSITION_ITEM_EDITOR_X,
        POSITION_ITEM_EDITOR_Y
    );

    itemOptions.setFont(fontItem);
    itemOptions.setString(STRING_OPTIONS);
    itemOptions.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemOptions.setColor(colorWhite);
    itemOptions.setPosition(
        POSITION_ITEM_OPTIONS_X,
        POSITION_ITEM_OPTIONS_Y
    );

    itemExit.setFont(fontItem);
    itemExit.setString(STRING_EXIT);
    itemExit.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
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

    soundBuffer.loadFromFile(constants::Sounds::getMoveSelectorSoundPath());

    soundSelectorMove.setBuffer(soundBuffer);

    titleRedDirection = DIRECTION_TITLE_RED_INIT;
    titleGreenDirection = DIRECTION_TITLE_GREEN_INIT;
    titleBlueDirection = DIRECTION_TITLE_BLUE_INIT;

    selectorPosition = 0;
}

/**
 *
 */
unsigned char MainMenuController::render(utils::Context* context)
{
    if(clock.getElapsedTime().asMilliseconds() >
            INTERVAL_ANIMATION_TITLE
      ) {
        animateTitleColor();
        clock.restart();
    }

    updateSelectorPosition();

    context->getWindow()->draw(title);
    context->getWindow()->draw(itemNewGame);
    context->getWindow()->draw(itemLoadGame);
    context->getWindow()->draw(itemEditor);
    context->getWindow()->draw(itemOptions);
    context->getWindow()->draw(itemExit);
    context->getWindow()->draw(spriteGithub);

    while(context->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Up: {
                        soundSelectorMove.play();

                        selectorPosition--;

                        break;
                    }
                    case sf::Keyboard::Down: {
                        soundSelectorMove.play();

                        selectorPosition++;

                        break;
                    }
                    case sf::Keyboard::Return: {
                        selectMenuItem(context->getWindow());

                        break;
                    }
                }
            }
        }
    }

    return nextControllerId;
}

/**
 *
 */
void MainMenuController::animateTitleColor()
{
    colorTitle.r += titleRedDirection;
    colorTitle.g += titleGreenDirection;
    colorTitle.b += titleBlueDirection;

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

/**
 *
 */
void MainMenuController::updateSelectorPosition()
{
    selectorPosition = (
                           (selectorPosition > MAIN_MENU_SELECTOR_MAX) ?
                           MAIN_MENU_SELECTOR_MIN :
                           selectorPosition
                       );

    itemNewGame.setColor(colorWhite);
    itemLoadGame.setColor(colorWhite);
    itemEditor.setColor(colorWhite);
    itemOptions.setColor(colorWhite);
    itemExit.setColor(colorWhite);

    switch(selectorPosition) {
        case MAIN_MENU_ITEM_NEW_GAME: {
            itemNewGame.setColor(colorRed);
            break;
        }
        case MAIN_MENU_ITEM_LOAD_GAME: {
            itemLoadGame.setColor(colorRed);
            break;
        }
        case MAIN_MENU_ITEM_EDITOR: {
            itemEditor.setColor(colorRed);
            break;
        }
        case MAIN_MENU_ITEM_OPTIONS: {
            itemOptions.setColor(colorRed);
            break;
        }
        case MAIN_MENU_ITEM_EXIT: {
            itemExit.setColor(colorRed);
            break;
        }
    }
}

/**
 *
 */
void MainMenuController::selectMenuItem(sf::RenderWindow* window)
{
    switch(selectorPosition) {
        case MAIN_MENU_ITEM_NEW_GAME: {
            nextControllerId = factories::ScreenFactory::NEW_GAME_CONTROLLER_ID;

            break;
        }
        case MAIN_MENU_ITEM_EDITOR: {
            nextControllerId = factories::ScreenFactory::EDITOR_SERIE_CONTROLLER_ID;

            break;
        }
        case MAIN_MENU_ITEM_EXIT: {
            window->close();

            break;
        }
    }
}
