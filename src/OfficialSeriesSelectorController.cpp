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
 * @file OfficialSeriesSelectorController.cpp
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "OfficialSeriesSelectorController.hpp"
#include "ControllerFactory.hpp"
#include "Colors.hpp"
#include "Fonts.hpp"

using namespace controllers;

const std::string OfficialSeriesSelectorController::OFF_SER_TITLE = "Official series";
const std::string OfficialSeriesSelectorController::TUTORIAL = "1. Tutorial";
const std::string OfficialSeriesSelectorController::FIRST_SERIE = "2. First serie";
const std::string OfficialSeriesSelectorController::SECOND_SERIE = "3. First serie";
const std::string OfficialSeriesSelectorController::THIRD_SERIE = "4. First serie";
const std::string OfficialSeriesSelectorController::FOURTH_SERIE = "5. First serie";
const std::string OfficialSeriesSelectorController::FIFTH_SERIE = "6. First serie";
const std::string OfficialSeriesSelectorController::SIXTH_SERIE = "7. First serie";
const std::string OfficialSeriesSelectorController::SEVENTH_SERIE = "8. First serie";

const float_t OfficialSeriesSelectorController::TUTORIAL_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::TUTORIAL_VRTL_PSTN = 200.f;
const float_t OfficialSeriesSelectorController::FIRST_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::FIRST_SERIE_VRTL_PSTN = 280.f;
const float_t OfficialSeriesSelectorController::SECOND_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::SECOND_SERIE_VRTL_PSTN = 360.f;
const float_t OfficialSeriesSelectorController::THIRD_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::THIRD_SERIE_VRTL_PSTN = 440.f;
const float_t OfficialSeriesSelectorController::FOURTH_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::FOURTH_SERIE_VRTL_PSTN = 520.f;
const float_t OfficialSeriesSelectorController::FIFTH_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::FIFTH_SERIE_VRTL_PSTN = 600.f;
const float_t OfficialSeriesSelectorController::SIXTH_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::SIXTH_SERIE_VRTL_PSTN = 680.f;
const float_t OfficialSeriesSelectorController::SEVENTH_SERIE_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::SEVENTH_SERIE_VRTL_PSTN = 760.f;
const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_HRTL_PSTN = 550.f;
const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_VRTL_PSTN = 50.f;

/**
 *
 */
OfficialSeriesSelectorController::OfficialSeriesSelectorController()
{
    fontItem.loadFromFile(constants::Fonts::getTextFontPath());
    fontTitle.loadFromFile(constants::Fonts::getTitleFontPath());

    colorWhite.r = constants::Colors::COLOR_WHITE_RED;
    colorWhite.g = constants::Colors::COLOR_WHITE_GREEN;
    colorWhite.b = constants::Colors::COLOR_WHITE_BLUE;
    colorWhite.a = constants::Colors::COLOR_ALPHA_FULL;

    colorSelector.r = constants::Colors::COLOR_RED_RED;
    colorSelector.g = constants::Colors::COLOR_RED_GREEN;
    colorSelector.b = constants::Colors::COLOR_RED_BLUE;
    colorSelector.a = constants::Colors::COLOR_ALPHA_FULL;

    colorTitle.r = constants::Colors::COLOR_LIGHT_BLUE_RED;
    colorTitle.g = constants::Colors::COLOR_LIGHT_BLUE_GREEN;
    colorTitle.b = constants::Colors::COLOR_LIGHT_BLUE_BLUE;
    colorTitle.a = constants::Colors::COLOR_ALPHA_FULL;

    offSerTitle.setFont(fontTitle);
    offSerTitle.setString(OFF_SER_TITLE);
    offSerTitle.setCharacterSize(constants::Fonts::SIZE_SUB_TITLE_FONT);
    offSerTitle.setColor(colorTitle);
    offSerTitle.setPosition(
        OFF_SER_TITLE_HRTL_PSTN,
        OFF_SER_TITLE_VRTL_PSTN
    );

    itemTutorial.setFont(fontItem);
    itemTutorial.setString(TUTORIAL);
    itemTutorial.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemTutorial.setColor(colorSelector);
    itemTutorial.setPosition(
        TUTORIAL_HRTL_PSTN,
        TUTORIAL_VRTL_PSTN
    );

    itemFirstSerie.setFont(fontItem);
    itemFirstSerie.setString(FIRST_SERIE);
    itemFirstSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemFirstSerie.setColor(colorWhite);
    itemFirstSerie.setPosition(
        FIRST_SERIE_HRTL_PSTN,
        FIRST_SERIE_VRTL_PSTN
    );

    itemSecondSerie.setFont(fontItem);
    itemSecondSerie.setString(SECOND_SERIE);
    itemSecondSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemSecondSerie.setColor(colorWhite);
    itemSecondSerie.setPosition(
        SECOND_SERIE_HRTL_PSTN,
        SECOND_SERIE_VRTL_PSTN
    );

    itemThirdSerie.setFont(fontItem);
    itemThirdSerie.setString(THIRD_SERIE);
    itemThirdSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemThirdSerie.setColor(colorWhite);
    itemThirdSerie.setPosition(
        THIRD_SERIE_HRTL_PSTN,
        THIRD_SERIE_VRTL_PSTN
    );

    itemFourthSerie.setFont(fontItem);
    itemFourthSerie.setString(FOURTH_SERIE);
    itemFourthSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemFourthSerie.setColor(colorWhite);
    itemFourthSerie.setPosition(
        FOURTH_SERIE_HRTL_PSTN,
        FOURTH_SERIE_VRTL_PSTN
    );

    itemFifthSerie.setFont(fontItem);
    itemFifthSerie.setString(FIFTH_SERIE);
    itemFifthSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemFifthSerie.setColor(colorWhite);
    itemFifthSerie.setPosition(
        FIFTH_SERIE_HRTL_PSTN,
        FIFTH_SERIE_VRTL_PSTN
    );

    itemSixthSerie.setFont(fontItem);
    itemSixthSerie.setString(SIXTH_SERIE);
    itemSixthSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemSixthSerie.setColor(colorWhite);
    itemSixthSerie.setPosition(
        SIXTH_SERIE_HRTL_PSTN,
        SIXTH_SERIE_VRTL_PSTN
    );

    itemSeventhSerie.setFont(fontItem);
    itemSeventhSerie.setString(SEVENTH_SERIE);
    itemSeventhSerie.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
    itemSeventhSerie.setColor(colorWhite);
    itemSeventhSerie.setPosition(
        SEVENTH_SERIE_HRTL_PSTN,
        SEVENTH_SERIE_VRTL_PSTN
    );

    selectorDirection = 1;
    selectorPosition = 0;
}

/**
 *
 */
uint8_t OfficialSeriesSelectorController::render(utils::Context* ctx)
{
    nextControllerId = animateScreenTransition(ctx);

    policies::HasMenuSelectorAnimation::animateMenuSelector<OfficialSeriesSelectorController>(this);

    updtSltrPstn();

    ctx->getWindow()->draw(offSerTitle);
    ctx->getWindow()->draw(itemTutorial);
    ctx->getWindow()->draw(itemFirstSerie);
    ctx->getWindow()->draw(itemSecondSerie);
    ctx->getWindow()->draw(itemThirdSerie);
    ctx->getWindow()->draw(itemFourthSerie);
    ctx->getWindow()->draw(itemFifthSerie);
    ctx->getWindow()->draw(itemSixthSerie);
    ctx->getWindow()->draw(itemSeventhSerie);

    while(ctx->getWindow()->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch(event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                expectedControllerId =
                    factories::ControllerFactory::MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* TODO: temporary solution, should be deleted */
            case sf::Keyboard::Return:
            {
                expectedControllerId =
                    factories::ControllerFactory::GAME_CONTROLLER_ID;

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
void OfficialSeriesSelectorController::updtSltrPstn()
{
    /* TODO: for now, the position is fixed. Only the first item is selected. */
    itemTutorial.setColor(colorSelector);
}
