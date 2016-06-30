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

#include "SoundsManager.hpp"
#include "fonts.hpp"
#include "controllers.hpp"

namespace memoris
{
namespace controllers
{

const std::string SerieMainMenuController::OFFICIAL_STR = "Official series";
const std::string SerieMainMenuController::PERSONAL_STR = "Personal series";
const std::string SerieMainMenuController::BACK_STR = "Back";
const std::string SerieMainMenuController::TITLE_STR = "Series";
const std::string SerieMainMenuController::CUP_IMG_PATH = "res/images/cup.png";
const std::string SerieMainMenuController::GAME_IMG_PATH = "res/images/game.png";

const float SerieMainMenuController::OFFICIAL_HRTL_PSTN = 550.f;
const float SerieMainMenuController::OFFICIAL_VRTL_PSTN = 250.f;
const float SerieMainMenuController::PERSONAL_HRTL_PSTN = 520.f;
const float SerieMainMenuController::PERSONAL_VRTL_PSTN = 470.f;
const float SerieMainMenuController::BACK_HRTL_PSTN = 720.f;
const float SerieMainMenuController::BACK_VRTL_PSTN = 800.f;
const float SerieMainMenuController::TITLE_HRTL_PSTN = 700.f;
const float SerieMainMenuController::TITLE_VRTL_PSTN = 50.f;
const float SerieMainMenuController::TRLST_COMMON_HRTL_PSTN = 740.f;
const float SerieMainMenuController::TRLST_COMMON_HRTL_SIZE = 200.f;
const float SerieMainMenuController::CUP_TRLST_VRTL_PSTN = 230.f;
const float SerieMainMenuController::GAME_TRLST_VRTL_PSTN = 450.f;

const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_SELECTOR_MAX = 2;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_SELECTOR_MIN = 0;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_OFFICIAL_ITEM = 0;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_PERSONAL_ITEM = 1;
const uint8_t SerieMainMenuController::SERIE_MAIN_MENU_BACK_ITEM = 2;

/**
 *
 */
SerieMainMenuController::SerieMainMenuController(utils::Context& context) :
    Controller(context),
    cupTrslt(
        TRLST_COMMON_HRTL_PSTN,
        CUP_TRLST_VRTL_PSTN,
        TRLST_COMMON_HRTL_SIZE
    ),
    gameTrslt(
        TRLST_COMMON_HRTL_PSTN,
        GAME_TRLST_VRTL_PSTN,
        TRLST_COMMON_HRTL_SIZE
    )
{
    context.getFontsManager().getTitleFont().loadFromFile(memoris::fonts::TITLE_FONT);
    context.getFontsManager().getTextFont().loadFromFile(memoris::fonts::TEXT_FONT);

    /* this color is continually updated, that's
       why this is a copy of the red color */
    colorSelector = context.getColorsManager().getColorRedCopy();

    title.setFont(context.getFontsManager().getTitleFont());
    title.setString(TITLE_STR);
    title.setCharacterSize(memoris::fonts::SUB_TITLE_SIZE);
    title.setColor(context.getColorsManager().getColorLightBlue());
    title.setPosition(
        TITLE_HRTL_PSTN,
        TITLE_VRTL_PSTN
    );

    itemOfficialSeries.setFont(context.getFontsManager().getTextFont());
    itemOfficialSeries.setString(OFFICIAL_STR);
    itemOfficialSeries.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemOfficialSeries.setColor(colorSelector);
    itemOfficialSeries.setPosition(
        OFFICIAL_HRTL_PSTN,
        OFFICIAL_VRTL_PSTN
    );

    itemPersonalSeries.setFont(context.getFontsManager().getTextFont());
    itemPersonalSeries.setString(PERSONAL_STR);
    itemPersonalSeries.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemPersonalSeries.setColor(context.getColorsManager().getColorWhite());
    itemPersonalSeries.setPosition(
        PERSONAL_HRTL_PSTN,
        PERSONAL_VRTL_PSTN
    );

    itemBack.setFont(context.getFontsManager().getTextFont());
    itemBack.setString(BACK_STR);
    itemBack.setCharacterSize(memoris::fonts::ITEM_SIZE);
    itemBack.setColor(context.getColorsManager().getColorWhite());
    itemBack.setPosition(
        BACK_HRTL_PSTN,
        BACK_VRTL_PSTN
    );

    cup.loadFromFile(CUP_IMG_PATH);
    game.loadFromFile(GAME_IMG_PATH);

    cupSprt.setTexture(cup, true);
    gameSprt.setTexture(game, true);

    selectorDirection = 1;
    selectorPosition = 0;

    animCup = true;
    animGame = false;
}

/**
 *
 */
unsigned short SerieMainMenuController::render(utils::Context& context)
{
    policies::HasMenuSelectorAnimation::animateMenuSelector<SerieMainMenuController>(this);

    updateSelectorPosition(context);

    cupTrslt.display(
        context,
        cupSprt,
        animCup
    );

    gameTrslt.display(
        context,
        gameSprt,
        animGame
    );

    context.getSfmlWindow().draw(title);
    context.getSfmlWindow().draw(itemOfficialSeries);
    context.getSfmlWindow().draw(itemPersonalSeries);
    context.getSfmlWindow().draw(itemBack);

    nextControllerId = animateScreenTransition(context);

    while (context.getSfmlWindow().pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
            {
                expectedControllerId =
                    MAIN_MENU_CONTROLLER_ID;

                break;
            }
            case sf::Keyboard::Up:
            {
                sounds::SoundsManager::get().getMoveSelectorSound().play();

                selectorPosition--;

                break;
            }
            case sf::Keyboard::Down:
            {
                sounds::SoundsManager::get().getMoveSelectorSound().play();

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
void SerieMainMenuController::updateSelectorPosition(utils::Context& context)
{
    selectorPosition = (
                           (selectorPosition > SERIE_MAIN_MENU_SELECTOR_MAX) ?
                           SERIE_MAIN_MENU_SELECTOR_MIN :
                           selectorPosition
                       );

    itemOfficialSeries.setColor(context.getColorsManager().getColorWhite());
    itemPersonalSeries.setColor(context.getColorsManager().getColorWhite());
    itemBack.setColor(context.getColorsManager().getColorWhite());

    animCup = false;
    animGame = false;

    switch (selectorPosition)
    {
    case SERIE_MAIN_MENU_OFFICIAL_ITEM:
    {
        itemOfficialSeries.setColor(colorSelector);
        animCup = true;
        break;
    }
    case SERIE_MAIN_MENU_PERSONAL_ITEM:
    {
        itemPersonalSeries.setColor(colorSelector);
        animGame = true;
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
        expectedControllerId =
            OFFICIAL_SERIES_SELECTOR_CONTROLLER_ID;

        break;
    }
    case SERIE_MAIN_MENU_BACK_ITEM:
    {
        expectedControllerId =
            MAIN_MENU_CONTROLLER_ID;

        break;
    }
    }
}

}
}
