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
 * Editor menu.
 *
 * @file EditorMenuController.hpp
 * @brief editor main menu
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_MENU
#define DEF_EDITOR_MENU

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Controller.hpp"

#include "HasMenuSelectorAnimation.hpp"

namespace controllers
{
class EditorMenuController : public Controller
{
    friend class policies::HasMenuSelectorAnimation;

    static const std::string STRING_LEVELS_EDITOR;
    static const std::string STRING_SERIES_EDITOR;
    static const std::string STRING_BACK;

    static const unsigned short POSITION_ITEM_LEVELS_EDITOR_X;
    static const unsigned short POSITION_ITEM_LEVELS_EDITOR_Y;

    static const unsigned short POSITION_ITEM_SERIES_EDITOR_X;
    static const unsigned short POSITION_ITEM_SERIES_EDITOR_Y;

    static const unsigned short POSITION_ITEM_BACK_X;
    static const unsigned short POSITION_ITEM_BACK_Y;

    static const unsigned short EDITOR_MENU_SELECTOR_MAX;
    static const unsigned short EDITOR_MENU_SELECTOR_MIN;

    static const unsigned short EDITOR_MENU_ITEM_LEVELS_EDITOR;
    static const unsigned short EDITOR_MENU_ITEM_SERIES_EDITOR;
    static const unsigned short EDITOR_MENU_ITEM_BACK;

public:

    EditorMenuController();

    /**
     * @brief render the serie editor screen
     *
     * @param context commons items for controller
     *
     * @return uint8_t   id of the next screen controller
     */
    uint8_t render(
        utils::Context& context
    );

    /**
     * @brief change the position of the cursor in the menu
     */
    void updateSelectorPosition();

    /**
     * @brief changes the controller id according to the selected menu item
     */
    void selectMenuItem();

private:

    unsigned short selectorPosition;

    short selectorDirection;

    sf::Font fontItem;

    sf::Color colorWhite;
    sf::Color colorSelector;

    sf::Text itemLevelsEditor;
    sf::Text itemSeriesEditor;
    sf::Text itemBack;

    sf::SoundBuffer soundBuffer;

    sf::Sound soundSelectorMove;
};
}

#endif
