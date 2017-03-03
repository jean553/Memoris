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
 * @file SelectionListWidget.hpp
 * @brief widget with textual items to select
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SELECTIONLISTWIDGET_H_
#define MEMORIS_SELECTIONLISTWIDGET_H_

#include <memory>
#include <vector>

namespace sf
{
class Sprite;
class Text;

template<typename T>
class Vector2;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace widgets
{

class SelectionListWidget
{

public:

    static constexpr short NO_SELECTION_INDEX {-1};

    /**
     * @brief indicates the list scroll movement
     */
    enum class ListMovement {
        Up, /** <- the items are moved down and visible index moved up */
        Down /** <- the items are moved up and visile index moved down */
    };

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param horizontalPosition the expected horizontal position of the widget
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    SelectionListWidget(
        const utils::Context& context,
        const float& horizontalPosition = 500.f
    );

    /**
     * @brief default destructor
     */
    ~SelectionListWidget();

    /**
     * @brief displays the widget
     *
     * @param cursorPosition the current position of the cursor
     *
     * calls SFML functions that are not noexcept
     */
    void display(const sf::Vector2<float>& cursorPosition) const &;

    /**
     * @brief getter of the current pointed item string
     *
     * @return const std::string
     *
     * sf::Text::getString() is not noexcept
     */
    const std::string getCurrentItem() const &;

    /**
     * @brief getter of the current list items amount
     *
     * @return const size_t
     */
    const size_t getItemsAmount() const & noexcept;

    /**
     * @brief getter of the current index
     *
     * @return const short&
     */
    const short& getCurrentIndex() const & noexcept;

    /**
     * @brief indicates if the list can be scrolled up
     *
     * @return const bool
     */
    const bool canScrollUp() const & noexcept;

    /**
     * @brief indicates if the list can be scrolled down
     *
     * @return const bool
     */
    const bool canScrollDown() const & noexcept;

    /**
     * @brief scroll the list in the given direction (movement)
     *
     * @param movement the movement to perform, up or down
     *
     * not noexcept because SFML sf::Text::setPosition() is not noexcept
     */
    void updateAllItemsPosition(const ListMovement& movement) const &;

    /**
     * @brief deletes the selected item
     *
     * not noexcept because SFML sf::Text::setPosition() is not noexcept
     */
    void deleteSelectedItem() const &;

    /**
     * @brief add one string into the displayed list
     *
     * @param text the text to display for the new item
     *
     * not noexcept because SFML sf::Text methods are not noexcept
     */
    void addItem(const std::string&& text) const &;

    /**
     * @brief getter of the stored values in the list
     *
     * @return const std::vector<sf::Text>&
     */
    const std::vector<sf::Text>& getTexts() const & noexcept;

    /**
     * @brief deletes all the items from the list; use std::vector<T>::clear()
     * which does not throw any exception
     */
    void deleteAllItems() const & noexcept;

protected:

    /**
     * @brief getter of the texts list
     *
     * @return std::vector<sf::Text>&
     *
     * this method has been created in order to let the children objects
     * modify the list, so, the returned std::vector is not constant
     */
    std::vector<sf::Text>& getList() const & noexcept;

    /**
     * @brief getter of the horizontal position
     *
     * @return const float&
     */
    const float& getHorizontalPosition() const & noexcept;

private:

    static constexpr float VERTICAL_POSITION {200.f};
    static constexpr float WIDTH {600.f};
    static constexpr float HEIGHT {600.f};
    static constexpr float ITEMS_SEPARATION {50.f};
    static constexpr float ARROWS_VERTICAL_POSITION {800.f};


    /**
     * @brief move the visual selector according to the current cursor position
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void displaySelector() const &;

    /**
     * @brief indicates if the mouse is currently on an item of the list
     *
     * @param cursorPosition the cursor current position
     *
     * @return const bool
     *
     * not noexcept because it calls SFML sf::Text::getPosition() method
     * and this method is not noexcept
     */
    const bool isMouseOverItem(const sf::Vector2<float>& cursorPosition)
        const &;

    /**
     * @brief selects an arrow if the mouse is hover
     *
     * @param horizontalPosition horizontal position of the arrow
     * @param cursorPosition the cursor current position
     * @param arrowSprite reference to the arrow sprite,
     * not constant as the color might be changed
     * @param selected reference to the selection boolean to update
     *
     * not noexcept as it calls SFML functions that are not noexcept
     */
    void selectArrowWhenMouseHover(
        const unsigned short& horizontalPosition,
        const sf::Vector2<float>& cursorPosition,
        sf::Sprite& arrowSprite,
        bool& selected
    ) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
