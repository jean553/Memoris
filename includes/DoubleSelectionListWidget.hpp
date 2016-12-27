/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @file DoubleSelectionListsWidget.hpp
 * @brief special widget that contains two selection lists; used to move
 * items from one list to another
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DOUBLESELECTIONLISTSWIDGET_H_
#define MEMORIS_DOUBLESELECTIONLISTSWIDGET_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class SelectionListWidget;

class DoubleSelectionListWidget
{

public:

    /**
     * @brief constructor, initialize the implementation
     *
     * @param context reference to the context to use
     *
     * not 'noexcept' because it calls SFML function that are not noexcept
     */
    DoubleSelectionListWidget(const utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~DoubleSelectionListWidget() noexcept;

    /**
     * @brief displays the two lists
     *
     * @param context reference to the context to use
     *
     * not 'noexcept' because it calls some SFML method that are not noexcept
     */
    void display(const utils::Context& context) const &;

    /**
     * @brief getter for the list that contains all the levels
     *
     * @return const widget::SelectionListWidget&
     */
    const widgets::SelectionListWidget& getLevelsList() const & noexcept;

    /**
     * @brief getter for the list that contains all the levels of the serie
     *
     * @return const widget::SelectionListWidget&
     */
    const widgets::SelectionListWidget& getSerieLevelsList() const & noexcept;

    /**
     * @brief reset the two lists; the 'all levels' list is refreshed with an
     * updated list of containing the levels and the serie levels list is 
     * cleared
     *
     * @param context constant reference to the context to use
     *
     * not noexcept because it calls functions that are not noexcept
     */
    void resetLists(const utils::Context& context) const &;

private:

    static constexpr char PERSONAL_LEVELS_PATH[] {"data/levels/personals"};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
