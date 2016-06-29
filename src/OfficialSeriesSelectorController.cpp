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

#include "fonts.hpp"
#include "FileWriter.hpp"
#include "controllers.hpp"

namespace memoris
{
namespace controllers
{

const std::string OfficialSeriesSelectorController::OFF_SER_TITLE = "Official series";
const std::string OfficialSeriesSelectorController::TEMPORARY_DEFAULT_SERIE = "data/series/1.serie";

const float OfficialSeriesSelectorController::OFF_SER_TITLE_HRTL_PSTN = 550.f;
const float OfficialSeriesSelectorController::OFF_SER_TITLE_VRTL_PSTN = 50.f;

/**
 *
 */
OfficialSeriesSelectorController::OfficialSeriesSelectorController(utils::Context& context) :
    Controller(context),
    scrlList(context)
{
    offSerTitle.setFont(context.getFontsManager().getTitleFont());
    offSerTitle.setString(OFF_SER_TITLE);
    offSerTitle.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    offSerTitle.setColor(context.getColorsManager().getColorLightBlue());
    offSerTitle.setPosition(
        OFF_SER_TITLE_HRTL_PSTN,
        OFF_SER_TITLE_VRTL_PSTN
    );

    /* TODO: load all the levels of the serie, should be adapted according to the selected serie */
    levels = utils::FileWriter::readFileWithSprt(TEMPORARY_DEFAULT_SERIE);

    /* generate the series names list */
    createItems(context);
}

/**
 *
 */
unsigned short OfficialSeriesSelectorController::render(utils::Context& context)
{
    scrlList.updtSltrPstn(context);

    context.getSfmlWindow().draw(offSerTitle);

    scrlList.display(context);

    nextControllerId = animateScreenTransition(context);

    while(context.getSfmlWindow().pollEvent(event))
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
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            /* TODO: temporary solution, should be deleted */
            case sf::Keyboard::Return:
            {
                /* TODO: the level should be specified according to the selected serie */
                context.setNxtLvlStrPath(levels[0]);

                expectedControllerId =
                    GAME_CONTROLLER_ID;

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
void OfficialSeriesSelectorController::createItems(utils::Context& context)
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
    scrlList.initFromStrArr(context, strList);

    /* display the suffix strings */
    scrlList.initFromStrArr(
        context,
        strListSfx,
        false
    );
}

}
}
