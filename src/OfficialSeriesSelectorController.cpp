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
const std::string OfficialSeriesSelectorController::TEMPORARY_DEFAULT_SERIE = "data/series/1.serie";

const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_HRTL_PSTN = 550.f;
const float_t OfficialSeriesSelectorController::OFF_SER_TITLE_VRTL_PSTN = 50.f;

/**
 *
 */
OfficialSeriesSelectorController::OfficialSeriesSelectorController()
{
    fontTitle.loadFromFile(constants::Fonts::getTitleFontPath());

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

    /* TODO: load all the levels of the serie, should be adapted according to the selected serie */
    levels = utils::FileWriter::readFileWithSprt(TEMPORARY_DEFAULT_SERIE);

    /* generate the series names list */
    createItems();
}

/**
 *
 */
uint8_t OfficialSeriesSelectorController::render(utils::Context* ctx)
{
    scrlList.updtSltrPstn();

    ctx->getSfmlWin().draw(offSerTitle);

    scrlList.display(ctx);

    nextControllerId = animateScreenTransition(ctx);

    while(ctx->getSfmlWin().pollEvent(event))
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
                /* TODO: the level should be specified according to the selected serie */
                ctx->setNxtLvlStrPath(levels[0]);

                expectedControllerId =
                    factories::ControllerFactory::GAME_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                scrlList.decSltrPstn();

                break;
            }
            case sf::Keyboard::Down:
            {
                scrlList.incSltrPstn();

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
void OfficialSeriesSelectorController::createItems()
{
    /* TODO: the list is generated here for
     * official series... maybe it should be
     * in a better place... */
    std::vector<std::string> strList =
    {
        "1. tutorial",
        "2. a serie",
        "3. another serie",
        "4. another serie",
        "5. another serie",
        "6. another serie",
        "7. another serie",
        "8. another serie",
        "9. another serie"
    };

    /* TODO: should display the amount of levels inside
     * each serie */
    std::vector<std::string> strListSfx =
    {
        /* TODO: temporary solution, only returns the amount of levels in the first serie */
        std::to_string(utils::FileWriter::getItemsAmnt(TEMPORARY_DEFAULT_SERIE)),
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9"
    };

    /* display the prefix strings */
    scrlList.initFromStrArr(strList);

    /* display the suffix strings */
    scrlList.initFromStrArr(
        strListSfx,
        false
    );
}
