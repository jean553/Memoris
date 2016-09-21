/*
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
 * @file TutorialWidget.hpp
 * @brief tutorial manager that displays the information into the tutorial
 * serie levels
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_TUTORIALWIDGET_H_
#define MEMORIS_TUTORIALWIDGET_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class TutorialWidget
{

public:

    /**
     * @brief constructor, empty, only used to initialize the implementation 
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because the method calls SFML functions that are not
     * noexcept
     */
    TutorialWidget(utils::Context& context);

    /**
     * @brief default destructor, empty, only declared in order to use the
     * forwarding declaration
     */
    ~TutorialWidget() noexcept;

    /**
     * @brief display the tutorial widget
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because the method calls SFML functions that are not
     * noexcept
     */
    void display(utils::Context& context) const &;

private:

    static constexpr float WIDTH {250.f};
    static constexpr float HEIGHT {100.f};
    static constexpr float HORIZONTAL_POSITION {10.f};
    static constexpr float VERTICAL_POSITION {10.f};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
