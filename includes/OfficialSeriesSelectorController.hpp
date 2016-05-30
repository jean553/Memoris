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
 * Official series selector menu
 *
 * @file OfficialSeriesSelectorController.hpp
 * @brief official series menu
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_OFFICIAL_SERIES_SELECTOR_MENU
#define DEF_OFFICIAL_SERIES_SELECTOR_MENU

#include "Controller.hpp"
#include "HasMenuSelectorAnimation.hpp"

namespace controllers
{
class OfficialSeriesSelectorController : public Controller
{
    friend class policies::HasMenuSelectorAnimation;

public:

    OfficialSeriesSelectorController();

    /**
     * @brief rendering method
     *
     * @param ctx current context
     *
     * @return uint8_t id of the next screen
     */
    uint8_t render(utils::Context* ctx);

private:

    /**
     * @brief update the color and the position of the menu selector
     */
    void updtSltrPstn();

    static const std::string TUTORIAL;
    static const std::string FIRST_SERIE;
    static const std::string SECOND_SERIE;
    static const std::string THIRD_SERIE;
    static const std::string FOURTH_SERIE;
    static const std::string FIFTH_SERIE;
    static const std::string SIXTH_SERIE;
    static const std::string SEVENTH_SERIE;
    static const std::string OFF_SER_TITLE;

    static const uint8_t TUTORIAL_ITEM;
    static const uint8_t FIRST_SERIE_ITEM;
    static const uint8_t SECOND_SERIE_ITEM;
    static const uint8_t THIRD_SERIE_ITEM;
    static const uint8_t FOURTH_SERIE_ITEM;
    static const uint8_t FIFTH_SERIE_ITEM;
    static const uint8_t SIXTH_SERIE_ITEM;
    static const uint8_t SEVENTH_SERIE_ITEM;
    static const uint8_t SLTR_MAX;
    static const uint8_t SLTR_MIN;

    static const float_t TUTORIAL_HRTL_PSTN;
    static const float_t TUTORIAL_VRTL_PSTN;
    static const float_t FIRST_SERIE_HRTL_PSTN;
    static const float_t FIRST_SERIE_VRTL_PSTN;
    static const float_t SECOND_SERIE_HRTL_PSTN;
    static const float_t SECOND_SERIE_VRTL_PSTN;
    static const float_t THIRD_SERIE_HRTL_PSTN;
    static const float_t THIRD_SERIE_VRTL_PSTN;
    static const float_t FOURTH_SERIE_HRTL_PSTN;
    static const float_t FOURTH_SERIE_VRTL_PSTN;
    static const float_t FIFTH_SERIE_HRTL_PSTN;
    static const float_t FIFTH_SERIE_VRTL_PSTN;
    static const float_t SIXTH_SERIE_HRTL_PSTN;
    static const float_t SIXTH_SERIE_VRTL_PSTN;
    static const float_t SEVENTH_SERIE_HRTL_PSTN;
    static const float_t SEVENTH_SERIE_VRTL_PSTN;
    static const float_t OFF_SER_TITLE_HRTL_PSTN;
    static const float_t OFF_SER_TITLE_VRTL_PSTN;

    int8_t selectorDirection;

    uint8_t sltrPstn;

    sf::Color colorWhite;
    sf::Color colorSelector;
    sf::Color colorTitle;

    sf::Font fontItem;
    sf::Font fontTitle;

    /* TODO: except the tutorial item, all the other items
     * are not used and just displayed to show the expected
     * final result */
    sf::Text itemTutorial;
    sf::Text itemFirstSerie;
    sf::Text itemSecondSerie;
    sf::Text itemThirdSerie;
    sf::Text itemFourthSerie;
    sf::Text itemFifthSerie;
    sf::Text itemSixthSerie;
    sf::Text itemSeventhSerie;

    sf::Text offSerTitle;
};
}

#endif
