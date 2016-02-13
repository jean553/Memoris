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
 * @file EditorMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorMenuController.hpp"

#include "../utils/ControllerFactory.hpp"

#include "../defines/Colors.hpp"
#include "../defines/Fonts.hpp"
#include "../defines/Sounds.hpp"

using namespace controllers;

const std::string EditorMenuController::STRING_LEVELS_EDITOR = "Levels";
const std::string EditorMenuController::STRING_SERIES_EDITOR = "Series";
const std::string EditorMenuController::STRING_BACK = "Back";

const unsigned short EditorMenuController::POSITION_ITEM_LEVELS_EDITOR_X = 680;
const unsigned short EditorMenuController::POSITION_ITEM_LEVELS_EDITOR_Y = 200;

const unsigned short EditorMenuController::POSITION_ITEM_SERIES_EDITOR_X = 690;
const unsigned short EditorMenuController::POSITION_ITEM_SERIES_EDITOR_Y = 350;

const unsigned short EditorMenuController::POSITION_ITEM_BACK_X = 715;
const unsigned short EditorMenuController::POSITION_ITEM_BACK_Y = 600;

const unsigned short EditorMenuController::EDITOR_MENU_SELECTOR_MAX = 2;
const unsigned short EditorMenuController::EDITOR_MENU_SELECTOR_MIN = 0;

const unsigned short EditorMenuController::EDITOR_MENU_ITEM_LEVELS_EDITOR = 0;
const unsigned short EditorMenuController::EDITOR_MENU_ITEM_SERIES_EDITOR = 1;
const unsigned short EditorMenuController::EDITOR_MENU_ITEM_BACK = 2;

/**
 *
 */
EditorMenuController::EditorMenuController() : Controller()
{
    fontItem.loadFromFile(constants::Fonts::getTextFontPath());

    selectorPosition = 0;

    colorWhite.r = constants::Colors::COLOR_WHITE_RED;
    colorWhite.g = constants::Colors::COLOR_WHITE_GREEN;
    colorWhite.b = constants::Colors::COLOR_WHITE_BLUE;
    colorWhite.a = constants::Colors::COLOR_ALPHA_FULL;

    colorRed.r = constants::Colors::COLOR_RED_RED;
    colorRed.g = constants::Colors::COLOR_RED_GREEN;
    colorRed.b = constants::Colors::COLOR_RED_BLUE;
    colorRed.a = constants::Colors::COLOR_ALPHA_FULL;

    itemLevelsEditor.setFont(fontItem);
    itemLevelsEditor.setString(STRING_LEVELS_EDITOR);
    itemLevelsEditor.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemLevelsEditor.setColor(colorRed);
    itemLevelsEditor.setPosition(
        POSITION_ITEM_LEVELS_EDITOR_X,
        POSITION_ITEM_LEVELS_EDITOR_Y
    );

    itemSeriesEditor.setFont(fontItem);
    itemSeriesEditor.setString(STRING_SERIES_EDITOR);
    itemSeriesEditor.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemSeriesEditor.setColor(colorWhite);
    itemSeriesEditor.setPosition(
        POSITION_ITEM_SERIES_EDITOR_X,
        POSITION_ITEM_SERIES_EDITOR_Y
    );

    itemBack.setFont(fontItem);
    itemBack.setString(STRING_BACK);
    itemBack.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemBack.setColor(colorWhite);
    itemBack.setPosition(
        POSITION_ITEM_BACK_X,
        POSITION_ITEM_BACK_Y
    );

    soundBuffer.loadFromFile(
        constants::Sounds::getMoveSelectorSoundPath()
    );

    soundSelectorMove.setBuffer(soundBuffer);
}

/**
 *
 */
unsigned short EditorMenuController::render(utils::Context* pContext)
{
    updateSelectorPosition();

    pContext->getWindow()->draw(itemLevelsEditor);
    pContext->getWindow()->draw(itemSeriesEditor);
    pContext->getWindow()->draw(itemBack);

    while (pContext->getWindow()->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
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
                        selectMenuItem();

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
void EditorMenuController::updateSelectorPosition()
{
    selectorPosition = (
                           (selectorPosition > EDITOR_MENU_SELECTOR_MAX) ?
                           EDITOR_MENU_SELECTOR_MIN :
                           selectorPosition
                       );

    itemLevelsEditor.setColor(colorWhite);
    itemSeriesEditor.setColor(colorWhite);
    itemBack.setColor(colorWhite);

    switch (selectorPosition) {
        case EDITOR_MENU_ITEM_LEVELS_EDITOR: {
            itemLevelsEditor.setColor(colorRed);
            break;
        }
        case EDITOR_MENU_ITEM_SERIES_EDITOR: {
            itemSeriesEditor.setColor(colorRed);
            break;
        }
        case EDITOR_MENU_ITEM_BACK: {
            itemBack.setColor(colorRed);
            break;
        }
    }
}

/**
 *
 */
void EditorMenuController::selectMenuItem()
{
    switch(selectorPosition) {
        case EDITOR_MENU_ITEM_LEVELS_EDITOR: {

            nextControllerId =
                factories::ControllerFactory::EDITOR_LEVEL_CONTROLLER_ID;

            break;
        }
        case EDITOR_MENU_ITEM_SERIES_EDITOR: {

            nextControllerId =
                factories::ControllerFactory::EDITOR_SERIE_CONTROLLER_ID;

            break;
        }
        case EDITOR_MENU_ITEM_BACK: {

            nextControllerId =
                factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

            break;
        }
    }
}
