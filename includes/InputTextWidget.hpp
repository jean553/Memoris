/**
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
 * @file InputTextWidget.hpp
 * @brief handles input text widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_INPUTTEXTWIDGET_H_
#define MEMORIS_INPUTTEXTWIDGET_H_

#include <memory>

namespace sf
{
class String;
class Event;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class InputTextWidget
{

public:

    /**
     * @brief constructor
     *
     * @param context the current context
     */
    InputTextWidget(const utils::Context& context);

    /**
     * @brief default destructor
     */
    ~InputTextWidget();

    /**
     * @brief render the widget and its content
     *
     * sf::RenderWindow::draw() and Context::getClockMillisecondsTime()
     * are not noexcept
     */
    void display() const &;

    /**
     * @brief update the displayed text according to the user input
     *
     * @param event SFML event manager
     *
     * calls sf::String methods that are not noexcept
     */
    void update(const sf::Event& event) const &;

    /**
     * @brief return the current displayed text
     *
     * @return const sf::String&
     *
     * sf::Text::getString() is not noexcept
     */
    const sf::String& getText() const &;

private:

    static constexpr float HORIZONTAL_POSITION {500.f};
    static constexpr float VERTICAL_POSITION {450.f};
    static constexpr float CURSOR_AND_BORDER_DISTANCE {5.f};

    /**
     * @brief get copy of keyboard selected character (from a to z)
     *
     * @param event the SFML events manager
     *
     * @return const char
     */
    const char getInputLetter(const sf::Event& event) const & noexcept;

    /**
     * @brief increments the cursor position
     *
     * sf::RectangleShape::setPosition() is not noexcept
     */
    void updateCursorPosition() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
