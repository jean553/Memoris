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
     */
    ScrollableListWidget();

    /**
     * @brief display the scrollable list widget
     *
     * @param ctx current context pointer
     */
    void display(utils::Context* ctx);

    /**
     * TODO
     */
    void initFromStrArr(const std::vector<std::string>& arr);

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
     */
    void updtSltrPstn();

private:

    static constexpr float_t SLTR_HRTL_PSTN = 20.f;
    static constexpr float_t SLTR_VRTL_PSTN = 200.f;
    static constexpr float_t SLTR_VRTL_SPRT = 80.f;

    static constexpr uint8_t ITEMS_AMNT = 8;

    uint8_t sltrPstn;

    std::vector<sf::Text> txtItems;

    sf::Font font;

    sf::Color colorSltr;
    sf::Color colorWhite;
};
}

#endif
