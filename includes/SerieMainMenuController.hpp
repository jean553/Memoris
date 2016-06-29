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
 * Serie main menu screen.
 *
 * @file SerieMainMenuController.hpp
 * @brief main menu for the serie selection
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SERIE_MAIN_MENU_CONTROLLER
#define DEF_SERIE_MAIN_MENU_CONTROLLER

#include "Controller.hpp"
#include "Context.hpp"
#include "HasMenuSelectorAnimation.hpp"
#include "SprtTransition.hpp"

namespace memoris
{
namespace controllers
{

class SerieMainMenuController : public Controller
{
    friend class policies::HasMenuSelectorAnimation;

public:

    SerieMainMenuController(utils::Context& context);

    /**
     * @brief render the serie editor screen
     *
     * @param context commons items for controller
     *
     * @return unsigned short id of the next screen controller
     */
    unsigned short render(utils::Context& context);

private:

    static const std::string OFFICIAL_STR;
    static const std::string PERSONAL_STR;
    static const std::string BACK_STR;
    static const std::string TITLE_STR;
    static const std::string CUP_IMG_PATH;
    static const std::string GAME_IMG_PATH;

    static const float OFFICIAL_HRTL_PSTN;
    static const float OFFICIAL_VRTL_PSTN;
    static const float PERSONAL_HRTL_PSTN;
    static const float PERSONAL_VRTL_PSTN;
    static const float BACK_HRTL_PSTN;
    static const float BACK_VRTL_PSTN;
    static const float TITLE_HRTL_PSTN;
    static const float TITLE_VRTL_PSTN;
    static const float TRLST_COMMON_HRTL_PSTN;
    static const float TRLST_COMMON_HRTL_SIZE;
    static const float CUP_TRLST_VRTL_PSTN;
    static const float GAME_TRLST_VRTL_PSTN;

    static const uint8_t SERIE_MAIN_MENU_SELECTOR_MAX;
    static const uint8_t SERIE_MAIN_MENU_SELECTOR_MIN;
    static const uint8_t SERIE_MAIN_MENU_OFFICIAL_ITEM;
    static const uint8_t SERIE_MAIN_MENU_PERSONAL_ITEM;
    static const uint8_t SERIE_MAIN_MENU_BACK_ITEM;

    uint8_t selectorPosition;

    int8_t selectorDirection;

    /* the color of the animated menu selector, we declare
       it here because this color is continually updated
       during the animation */
    sf::Color colorSelector;

    sf::Text itemOfficialSeries;
    sf::Text itemPersonalSeries;
    sf::Text itemBack;
    sf::Text title;

    sf::Texture cup;
    sf::Texture game;

    sf::Sprite cupSprt;
    sf::Sprite gameSprt;

    utils::SprtTransition cupTrslt;
    utils::SprtTransition gameTrslt;

    bool animCup;
    bool animGame;

    /**
     * @brief update the position of the selector
     *
     * @param context current context
     */
    void updateSelectorPosition(utils::Context& context);

    /**
     * @brief execute an action according to the current menu selection
     */
    void selectMenuItem();
};

}
}

#endif
