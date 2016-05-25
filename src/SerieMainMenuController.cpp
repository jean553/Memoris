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
 * @file SerieMainMenuController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "SerieMainMenuController.hpp"
#include "ControllerFactory.hpp"
#include "Fonts.hpp"
#include "Colors.hpp"
#include "Sounds.hpp"

using namespace controllers;

const std::string SerieMainMenuController::OFFICIAL_STR = "Official series";
const std::string SerieMainMenuController::PERSONAL_STR = "Personal series";
const std::string SerieMainMenuController::BACK_STR = "Back";

const float_t SerieMainMenuController::OFFICIAL_HRTL_PSTN = 300.f;
const float_t SerieMainMenuController::OFFICIAL_VRTL_PSTN = 100.f;
const float_t SerieMainMenuController::PERSONAL_HRTL_PSTN = 300.f;
const float_t SerieMainMenuController::PERSONAL_VRTL_PSTN = 300.f;
const float_t SerieMainMenuController::BACK_HRTL_PSTN = 300.f;
const float_t SerieMainMenuController::BACK_VRTL_PSTN = 500.f;

const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_SELECTOR_MAX = 2;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_SELECTOR_MIN = 0;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_OFFICIAL_ITEM = 0;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_PERSONAL_ITEM = 1;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_BACK_ITEM = 2;

/**
 *
 */
SerieMainMenuController::SerieMainMenuController()
{
    fontItem.loadFromFile(constants::Fonts::getTextFontPath());

    colorWhite.r = constants::Colors::COLOR_WHITE_RED;
    colorWhite.g = constants::Colors::COLOR_WHITE_GREEN;
    colorWhite.b = constants::Colors::COLOR_WHITE_BLUE;
    colorWhite.a = constants::Colors::COLOR_ALPHA_FULL;

    colorSelector.r = constants::Colors::COLOR_RED_RED;
    colorSelector.g = constants::Colors::COLOR_RED_GREEN;
    colorSelector.b = constants::Colors::COLOR_RED_BLUE;
    colorSelector.a = constants::Colors::COLOR_ALPHA_FULL;

    itemOfficialSeries.setFont(fontItem);
    itemOfficialSeries.setString(OFFICIAL_STR);
    itemOfficialSeries.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemOfficialSeries.setColor(colorSelector);
    itemOfficialSeries.setPosition(
        OFFICIAL_HRTL_PSTN,
        OFFICIAL_VRTL_PSTN
    );

    itemPersonalSeries.setFont(fontItem);
    itemPersonalSeries.setString(PERSONAL_STR);
    itemPersonalSeries.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemPersonalSeries.setColor(colorWhite);
    itemPersonalSeries.setPosition(
        PERSONAL_HRTL_PSTN,
        PERSONAL_VRTL_PSTN
    );

    itemBack.setFont(fontItem);
    itemBack.setString(BACK_STR);
    itemBack.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemBack.setColor(colorWhite);
    itemBack.setPosition(
        BACK_HRTL_PSTN,
        BACK_VRTL_PSTN
    );

    soundBfr.loadFromFile(constants::Sounds::MOVE_SELECTOR_SOUND_PATH);

    selectorMoveSnd.setBuffer(soundBfr);

    selectorDirection = 1;
    selectorPosition = 0;
}

/**
 *
 */
uint8_t SerieMainMenuController::render(utils::Context* ctx)
{
    policies::HasMenuSelectorAnimation::animateMenuSelector<SerieMainMenuController>(this);

    updateSelectorPosition();

    ctx->getWindow()->draw(itemOfficialSeries);
    ctx->getWindow()->draw(itemPersonalSeries);
    ctx->getWindow()->draw(itemBack);

    nextControllerId = animateScreenTransition(ctx);

    while (ctx->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                nextControllerId =
                    factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                selectorMoveSnd.play();

                selectorPosition--;

                break;
            }
            case sf::Keyboard::Down:
            {
                selectorMoveSnd.play();

                selectorPosition++;

                break;
            }
            case sf::Keyboard::Return:
            {
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
void SerieMainMenuController::updateSelectorPosition()
{
    selectorPosition = (
                           (selectorPosition > SERIE_MAIN_MENU_SELECTOR_MAX) ?
                           SERIE_MAIN_MENU_SELECTOR_MIN :
                           selectorPosition
                       );

    itemOfficialSeries.setColor(colorWhite);
    itemPersonalSeries.setColor(colorWhite);
    itemBack.setColor(colorWhite);

    switch (selectorPosition)
    {
    case SERIE_MAIN_MENU_OFFICIAL_ITEM:
    {
        itemOfficialSeries.setColor(colorSelector);
        break;
    }
    case SERIE_MAIN_MENU_PERSONAL_ITEM:
    {
        itemPersonalSeries.setColor(colorSelector);
        break;
    }
    case SERIE_MAIN_MENU_BACK_ITEM:
    {
        itemBack.setColor(colorSelector);
        break;
    }
    }
}

/**
 *
 */
void SerieMainMenuController::selectMenuItem()
{
    switch(selectorPosition)
    {
    case SERIE_MAIN_MENU_OFFICIAL_ITEM:
    {
        /* TODO: temporary solution, should redirect to another menu */
        expectedControllerId =
            factories::ControllerFactory::GAME_CONTROLLER_ID;

        break;
    }
    case SERIE_MAIN_MENU_BACK_ITEM:
    {
        expectedControllerId =
            factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

        break;
    }
    }
}
