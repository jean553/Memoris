/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief displays and handles the input text widget
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
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    InputTextWidget(const utils::Context& context);

    InputTextWidget(const InputTextWidget&) = delete;

    InputTextWidget& operator=(const InputTextWidget&) = delete;

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
     * @param newCharacter the new character to add to the displayed string
     *
     * calls sf::String methods that are not noexcept
     */
    void update(const char& newCharacter) const &;

    /**
     * @brief return the current displayed text
     *
     * @return const sf::String&
     *
     * sf::Text::getString() is not noexcept
     */
    const sf::String& getText() const &;

    /**
     * @brief check if the input text widget is full
     *
     * @return const bool
     *
     * sf::Text::getString() is not noexcept
     */
    const bool isFull() const &;

    /**
     * @brief get copy of keyboard selected character (from a to z);
     * refactor into a private method for readability
     *
     * @param event the SFML events manager
     *
     * @return const char
     */
    const char getInputLetter(const sf::Event& event) const & noexcept;

    /**
     * @brief check if the input text widget is empty
     *
     * @return const bool
     *
     * sf::Text::getString() is not noexcept
     */
    const bool isEmpty() const &;

    /**
     * @brief empty the displayed string
     */
    void empty() const & noexcept;

private:

    /**
     * @brief updates the position of the cursor according to the string size
     *
     * this method is called when the widget content is empty and
     * when a new character is appended to the displayed string
     *
     * not noexcept because it calls the SFML setPosition method
     */
    void updateCursorPosition() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
