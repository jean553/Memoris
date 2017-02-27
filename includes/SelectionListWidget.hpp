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
     * @param context the current context to use
     * @param cursorPosition the current position of the cursor
     *
     * calls SFML functions that are not noexcept
     */
    void display(
        const utils::Context& context,
        const sf::Vector2<float>& cursorPosition
    ) const &;

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
     * @brief updates the displayed items list if an arrow is clicked
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateList() const &;

    /**
     * @brief deletes the selected item
     *
     * not noexcept because it calls SFML methods, STL containers and iterators
     * methods that are not noexcept
     */
    void deleteSelectedItem() const &;

    /**
     * @brief add one string into the displayed list
     *
     * @param context constant reference to the current context to use
     * @param item constant reference to the string to insert
     */
    void addItem(
        const utils::Context& context,
        const std::string& item
    ) const &;

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

    /**
     * @brief checks if an item is selected or not
     *
     * @return const bool
     */
    const bool isAnyItemSelected() const & noexcept;

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
     * @param context the current context to use
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void displaySelector(const utils::Context& context) const &;

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
     * @param context constant reference to the current context
     * @param horizontalPosition horizontal position of the arrow
     * @param cursorPosition the cursor current position
     * @param arrowSprite reference to the arrow sprite,
     * not constant as the color might be changed
     * @param selected reference to the selection boolean to update
     *
     * not noexcept as it calls SFML functions that are not noexcept
     */
    void selectArrowWhenMouseHover(
        const utils::Context& context,
        const unsigned short& horizontalPosition,
        const sf::Vector2<float>& cursorPosition,
        sf::Sprite& arrowSprite,
        bool& selected
    ) const &;

    /**
     * @brief updates the position of all the items on the list according
     * to the user clicks on the arrow buttons
     *
     * @param movement constant reference to the movement (1 or -1)
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateAllItemsPosition(const float& movement) const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
