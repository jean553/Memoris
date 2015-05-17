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
 * @file EditorMainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "EditorMainMenuController.hpp"

using namespace controllers;

/**
 *
 */
EditorMainMenuController::EditorMainMenuController() : Controller()
{
    selectorPosition = 0;

    fontTitle.loadFromFile(PATH_FONT_TITLE);
    fontItem.loadFromFile(PATH_FONT_TEXT);

    colorTitle.r = COLOR_LIGHT_BLUE_RED;
    colorTitle.g = COLOR_LIGHT_BLUE_GREEN;
    colorTitle.b = COLOR_LIGHT_BLUE_BLUE;
    colorTitle.a = COLOR_ALPHA_FULL;

    colorWhite.r = COLOR_WHITE_RED;
    colorWhite.g = COLOR_WHITE_GREEN;
    colorWhite.b = COLOR_WHITE_BLUE;
    colorWhite.a = COLOR_ALPHA_FULL;

    colorRed.r = COLOR_RED_RED;
    colorRed.g = COLOR_RED_GREEN;
    colorRed.b = COLOR_RED_BLUE;
    colorRed.a = COLOR_ALPHA_FULL;

    titleEditor.setFont(fontTitle);
    titleEditor.setString(STRING_EDITOR);
    titleEditor.setCharacterSize(SIZE_SUB_TITLE_FONT);
    titleEditor.setColor(colorTitle);
    titleEditor.setPosition(
        POSITION_EDITOR_TITLE_X,
        POSITION_EDITOR_TITLE_Y
    );

    itemNewSerie.setFont(fontItem);
    itemNewSerie.setString(STRING_NEW_SERIE);
    itemNewSerie.setCharacterSize(SIZE_ITEM_FONT);
    itemNewSerie.setColor(colorRed);
    itemNewSerie.setPosition(
        POSITION_ITEM_EDITOR_NEW_SERIE_X,
        POSITION_ITEM_EDITOR_NEW_SERIE_Y
    );

    itemOpenSerie.setFont(fontItem);
    itemOpenSerie.setString(STRING_OPEN_SERIE);
    itemOpenSerie.setCharacterSize(SIZE_ITEM_FONT);
    itemOpenSerie.setColor(colorWhite);
    itemOpenSerie.setPosition(
        POSITION_ITEM_EDITOR_OPEN_SERIE_X,
        POSITION_ITEM_EDITOR_OPEN_SERIE_Y
    );

    soundBufferMove.loadFromFile(SOUND_SELECTOR_MOVE);
    soundBufferSelect.loadFromFile(SOUND_SELECTOR_SELECT);

    soundSelectorMove.setBuffer(soundBufferMove);
    soundSelectorSelect.setBuffer(soundBufferSelect);

    soundSelectorSelect.play();
}

/**
 *
 */
EditorMainMenuController::~EditorMainMenuController()
{
}

/**
 *
 */
unsigned char EditorMainMenuController::render(utils::Context* context)
{
    context->getWindow()->draw(titleEditor);
    context->getWindow()->draw(itemNewSerie);
    context->getWindow()->draw(itemOpenSerie);

    updateSelectorPosition();

    while(context->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                    {
                        nextControllerId = MAIN_MENU_CONTROLLER_ID;

                        break;
                    }

                    // move the selector
                    case sf::Keyboard::Up:
                    {
                        soundSelectorMove.play();

                        selectorPosition--;

                        break;
                    }
                    case sf::Keyboard::Down:
                    {
                        soundSelectorMove.play();

                        selectorPosition++;

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
void EditorMainMenuController::updateSelectorPosition()
{
    // fix selector position
    selectorPosition = (
        (selectorPosition > EDITOR_MAIN_MENU_SELECTOR_MAX) ?
        EDITOR_MAIN_MENU_SELECTOR_MIN :
        selectorPosition
    );

    // switch back all items color to white
    itemNewSerie.setColor(colorWhite);
    itemOpenSerie.setColor(colorWhite);

    switch(selectorPosition)
    {
        case EDITOR_MENU_ITEM_NEW_SERIE:
        {
            itemNewSerie.setColor(colorRed);

            break;
        }
        case EDITOR_MENU_ITEM_OPEN_SERIE:
        {
            itemOpenSerie.setColor(colorRed);

            break;
        }
    }
}
