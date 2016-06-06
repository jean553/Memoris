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
#include "FileWriter.hpp"

using namespace controllers;

const std::string OfficialSeriesSelectorController::OFF_SER_TITLE = "Official series";
const std::string OfficialSeriesSelectorController::TUTORIAL = "1. Tutorial";
const std::string OfficialSeriesSelectorController::TEMPORARY_DEFAULT_SERIE = "data/series/1.serie";

/* TODO: should be another kind of arrow, keep this one for now... */
const std::string OfficialSeriesSelectorController::ARR_DOWN_IMG_PATH = "res/images/down.png";

const uint8_t OfficialSeriesSelectorController::ITEMS_AMNT = 8;

const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_HRTL_PSTN = 550.f;
const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_VRTL_PSTN = 50.f;
const float_t OfficialSeriesSelectorController::ARR_DOWN_HRTL_PSTN = 790.f;
const float_t OfficialSeriesSelectorController::ARR_DOWN_VRTL_PSTN = 850.f;
const float_t OfficialSeriesSelectorController::SLTR_HRTL_PSTN = 20.f;
const float_t OfficialSeriesSelectorController::SLTR_VRTL_PSTN = 200.f;
const float_t OfficialSeriesSelectorController::SLTR_VRTL_SPRT = 80.f;

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

    arrDownTxt.loadFromFile(ARR_DOWN_IMG_PATH);

    arrDownSprt.setTexture(arrDownTxt);
    arrDownSprt.setPosition(
        ARR_DOWN_HRTL_PSTN,
        ARR_DOWN_VRTL_PSTN
    );

    selectorDirection = 1;
    sltrPstn = 0;

    /* generate the series names list */
    createItems();
}

/**
 *
 */
uint8_t OfficialSeriesSelectorController::render(utils::Context* ctx)
{
    policies::HasMenuSelectorAnimation::animateMenuSelector<OfficialSeriesSelectorController>(this);

    updtSltrPstn();

    ctx->getWindow()->draw(offSerTitle);
    ctx->getWindow()->draw(arrDownSprt);

    for (sf::Text& item : txtItems)
    {
        ctx->getWindow()->draw(item);
    }

    nextControllerId = animateScreenTransition(ctx);

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
                /* TODO: load all the levels of the serie, should be adapted according to the selected serie */
                std::vector<std::string> levels = utils::FileWriter::readFileWithSprt(TEMPORARY_DEFAULT_SERIE);

                /* TODO: the level should be specified according to the selected serie */
                ctx->setNxtLvlStrPath(levels[0]);

                expectedControllerId =
                    factories::ControllerFactory::GAME_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                sltrPstn--;

                break;
            }
            case sf::Keyboard::Down:
            {
                sltrPstn++;

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
    sltrPstn = ((sltrPstn > ITEMS_AMNT - 1) ? 0 : sltrPstn);

    for (sf::Text& item : txtItems)
    {
        item.setColor(colorWhite);
    }

    txtItems[sltrPstn].setColor(colorSelector);
}

/**
 *
 */
void OfficialSeriesSelectorController::createItems()
{
    for (uint8_t i = 0; i < ITEMS_AMNT; i++)
    {
        sf::Text txt;

        txt.setFont(fontItem);
        txt.setString(TUTORIAL);
        txt.setCharacterSize(constants::Fonts::SIZE_ITEM_FONT);
        txt.setColor(colorSelector);
        txt.setPosition(
            SLTR_HRTL_PSTN,
            SLTR_VRTL_PSTN + SLTR_VRTL_SPRT * i
        );

        txtItems.push_back(txt);
    }
}
