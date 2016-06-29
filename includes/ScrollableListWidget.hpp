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
 * Keyboard scrollable strings list
 *
 * @file ScrollableListWidget.hpp
 * @brief a scrollable strings list with animated arrows
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_SCROLLABLE_LIST_WIDGET
#define DEF_SCROLLABLE_LIST_WIDGET

#include "Widget.hpp"

namespace widgets
{
class ScrollableListWidget : public Widget
{
public:

    /**
     * @brief constructor
     *
     * @param context current context reference
     */
    ScrollableListWidget(utils::Context& context);

    /**
     * @brief display the scrollable list widget
     *
     * @param context current context pointer
     */
    void display(utils::Context& context);

    /**
     * @brief initialize the strings list from a string vector
     *
     * @param context unique context
     * @param arr array of strings
     * @param side side where the strings have to be displayed
     */
    void initFromStrArr(
        utils::Context& context,
        const std::vector<std::string>& arr,
        const bool& isPrefix = true
    );

    /**
     * @brief increment the position of the selector
     */
    void incSltrPstn();

    /**
     * @brief decrement the position of the selector
     */
    void decSltrPstn();

    /**
     * @brief update the color and the position of the menu selector
     *
     * @param context current context reference
     */
    void updtSltrPstn(utils::Context& context);

private:

    /**
     * @brief displays the arrow down and animate it
     *
     * @param context pointer to the current context object
     */
    void displayArrDown(utils::Context& context);

    static constexpr float SLTR_HRTL_PSTN = 20.f;
    static constexpr float SLTR_HRTL_PSTN_SUFFIX = 1500.f;
    static constexpr float SLTR_VRTL_PSTN = 200.f;
    static constexpr float SLTR_VRTL_SPRT = 80.f;

    static constexpr uint8_t ITEMS_AMNT = 8;
    static constexpr uint8_t TIME_ITRVL = 10;
    static constexpr uint8_t COLOR_ITRVL = 5;

    static constexpr float ARR_DOWN_HRTL_PSTN = 790.f;
    static constexpr float ARR_DOWN_VRTL_PSTN = 850.f;

    static const std::string ARR_DOWN_IMG_PATH;

    uint8_t sltrPstn;

    int8_t animDirection;

    std::vector<sf::Text> txtItems;
    std::vector<sf::Text> txtSfx;

    /* the color of the animated arrow; declared here
       as the color is animated and is modified
       continually */
    sf::Color colorArrow;

    sf::Texture arrDownTxt;

    sf::Sprite arrDownSprt;

    sf::Clock clk;
};
}

#endif
