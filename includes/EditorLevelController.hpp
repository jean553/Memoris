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
 * Editor of levels.
 *
 * @file EditorLevelController.hpp
 * @brief levels editor
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_EDITOR_LEVEL_CONTROLLER
#define DEF_EDITOR_LEVEL_CONTROLLER

#include <SFML/Graphics.hpp>

#include "Controller.hpp"
#include "ButtonWidget.hpp"
#include "CursorWidget.hpp"
#include "TitleBarWidget.hpp"
#include "InputTextWidget.hpp"
#include "CellSelectorWidget.hpp"
#include "Level.hpp"
#include "FrameWidget.hpp"

namespace memoris
{
namespace controllers
{

class EditorLevelController : public Controller
{

    static const std::string EDITOR_LEVEL_BUTTON_EXIT_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_NEW_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_OPEN_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_SAVE_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_NEXT_FLOOR_TEXT;
    static const std::string EDITOR_LEVEL_BUTTON_PREVIOUS_FLOOR_TEXT;
    static const std::string STRING_EDITOR_LEVEL_TITLE;
    static const std::string STRING_NEW_LEVEL_ERROR;
    static const std::string STRING_SAVE_LEVEL_ERROR;
    static const std::string STRING_FLOOR_PREFIX_LABEL;

    static const unsigned short LEVEL_EDITOR_BUTTONS_POSITION_X;
    static const unsigned short LEVEL_EDITOR_BUTTON_NEW_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_OPEN_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_SAVE_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_LEVEL_UP_POSITION_Y;
    static const unsigned short LEVEL_EDITOR_BUTTON_LEVEL_DOWN_POSITION_Y;
    static const unsigned short LEVEL_POSITION_X;
    static const unsigned short LEVEL_POSITION_Y;
    static const unsigned short CELL_SELECTOR_POSITION_X;
    static const unsigned short CELL_SELECTOR_POSITION_Y;
    static const unsigned short ERROR_MESSAGE_POSITION_X;
    static const unsigned short ERROR_MESSAGE_POSITION_Y;
    static const unsigned short POSITION_NEW_LEVEL_INPUT_TEXT_X;
    static const unsigned short POSITION_NEW_LEVEL_INPUT_TEXT_Y;
    static const unsigned short SIZE_NEW_LEVEL_TEXT;
    static const float FLOOR_SELECTION_FRAME_HORIZONTAL_SIZE;
    static const float FLOOR_SELECTION_FRAME_VERTICAL_SIZE;
    static const float FLOOR_SELECTION_FRAME_HORIZONTAL_POSITION;
    static const float FLOOR_SELECTION_FRAME_VERTICAL_POSITION;
    static const float FLOOR_PREFIX_LABEL_HORIZONTAL_POSITION;
    static const float FLOOR_PREFIX_LABEL_VERTICAL_POSITION;
    static const float FLOOR_LABEL_HORIZONTAL_POSITION;
    static const float FLOOR_LABEL_VERTICAL_POSITION;

public:

    EditorLevelController();

    /**
     * @brief renders the level editor screen
     *
     * @param context commons items for controller
     *
     * @return uint8_t    id of the new screen controller
     */
    uint8_t render(utils::Context& context);

private:

    uint8_t currentFloor;

    enum EditorLevelStatus
    {
        MAIN_MENU,
        NEW_LEVEL,
        EDIT_LEVEL
    };

    EditorLevelStatus status;

    widgets::ButtonWidget buttonExit;
    widgets::ButtonWidget buttonNew;
    widgets::ButtonWidget buttonOpen;
    widgets::ButtonWidget buttonSave;
    widgets::ButtonWidget buttonNextFloor;
    widgets::ButtonWidget buttonPreviousFloor;

    widgets::FrameWidget floorSelectionFrame;

    widgets::CursorWidget cursor;

    widgets::TitleBarWidget titleBar;

    widgets::InputTextWidget inputTextNew;

    widgets::CellSelectorWidget cellSelector;

    entities::Level level;

    sf::Font levelNameLabelFont;

    sf::Color levelNameLabelColor;
    sf::Color levelNameLabelUnsavedColor;
    sf::Color errorLabelColor;

    sf::Text levelNameLabel;
    sf::Text errorLabel;
    sf::Text floorPrefixLabel;
    sf::Text floorLabel;

    bool levelAlreadyExists;
    bool saveLevelError;

    /**
     * @brief check if a level name already exists
     *
     * @param levelName name of the level
     *
     * @return boolean
     */
    bool levelExists(std::string levelName);

    /**
     * @brief change the color of the level name
     * according if the file is saved or not
     *
     * @param saved boolean of the value to display
     */
    void displaySavedLevelName(bool saved);

    /**
     * @brief update one cell of the level grid
     *
     * @param pSelectedCell pointer to the selected cell to update
     * @param pCellsSelectorCell pointer to the selected cell from selector to use
     */
    void updateOneCell(
        entities::Cell* pSelectedCell,
        entities::Cell* pCellsSelectorCell
    );

    /**
     * @brief update the current floor level according to the
     * given updateValue ( 1 or -1 ), 0 by default
     *
     * @param updateValue update to apply on the current floor
     */
    void updateFloorNumber(short updateValue);

    /**
     * @brief update the level according to the new added cell
     *
     * @param pSelectedCell pointer to the selected cell to update
     * @param pCellsSelectorCell pointer to the selected cell from selector to use
     * @param prevCellStr string representation of the previous cell at the same position
     */
    void updtLevelForSpecCells(
        entities::Cell* pSelectedCell,
        entities::Cell* pCellsSelectorCell,
        std::string prevCellStr
    );

    /**
     * @brief returns true if the current cell selector widget cell
     * can be added at the given location
     *
     * @return boolean
     */
    bool currEditIsAllowed();
};

}
}

#endif
