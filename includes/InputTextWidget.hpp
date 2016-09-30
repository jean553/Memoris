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
 * @file InputTextWidget.hpp
 * @brief the input text widget is a text line where the user can type text
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_INPUTTEXTWIDGET_H_
#define MEMORIS_INPUTTEXTWIDGET_H_

#include <SFML/Config.hpp>

#include <memory>
#include <stddef.h>

namespace sf
{
class RectangleShape;
class Text;
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
     * @brief constructor, initializes the implementation
     *
     * @param context reference to the current context
     * @param hPosition horizontal position
     * @param vPosition vertical position
     * @param lineWidth the width of the input text widget
     * @param maxCharacters the maximum amount of characters allowed
     */
    InputTextWidget(
        utils::Context& context,
        const float& hPosition,
        const float& vPosition,
        const float& lineWidth,
        const size_t& maxCharacters
    ) noexcept;

    /**
     * @brief default destructor, empty, only declared here in order to use
     * forwarding declaration
     */
    ~InputTextWidget() noexcept;

    /**
     * @brief set the displayed text; this function is used to force the
     * content of the input text widget; this function is used by the
     * level editor to edit the name of the current edited level
     *
     * @param inputTextData reference of a string to display into the input
     * text widget
     *
     * not 'const' because it modifies the displayed text in SFML text
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void setDisplayedText(const sf::String& inputTextData) &;

    /**
     * @brief render the widget and its content
     *
     * @param context reference to the current context to use
     *
     * not 'const' because it modifies the displayed cursor attribute and
     * flashing animation cursor
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void display(const utils::Context& context) &;

    /**
     * @brief update the displayed text according to the user input
     *
     * @param event constant reference to the SFML events manager
     *
     * not 'const' because it modifies the displayed text attribute
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void update(const sf::Event& event) &;

    /**
     * @brief return the current displayed text; return a copy of the string
     * for manipulation in calling object
     *
     * @return const sf::String&
     *
     * NOTE: the string we return is not an attribute of the widget class
     * but directly the string contained inside the SFML text object; this
     * avoid duplication of identical data
     */
    const sf::String& getText() const;

    /**
     * @brief returns a boolean indicating if the input text widget content
     * is empty or not; used into the new game controller to save the new
     * game only if the name is not empty
     *
     * @return const bool
     *
     * the returned bool is not a reference but a copied value because the
     * value is got from a function that already returns a copy and not a
     * reference
     *
     * not 'noexcept' because it calls isEmpty() function of the SFML and this
     * method is not marked as noexcept
     */
    const bool isEmpty() const &;

private:

    /**
     * @brief return a copy of the letter selected by the user on the keyboard;
     * this function uses the SFML events manager
     *
     * @param event constant reference to the SFML events manager
     *
     * @return const sf::String
     */
    const sf::String getInputLetter(const sf::Event& event) &;

    /**
     * @brief check if the keyspace key is pressed down, returns True if
     * pressed down, False is released
     *
     * @param event constant reference to the SFML events manager
     *
     * @return const bool
     */
    const bool backspaceIsPressedDown(const sf::Event& event) & noexcept;

    /**
     * @brief refactor of the action that update the position of the cursor
     * according of the current widget content graphical width
     *
     * not 'const' because it modifies the cursor attribute
     *
     * not 'noexcept' because it calls SFML functions that are not noexcept
     */
    void updateCursorPosition() &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
