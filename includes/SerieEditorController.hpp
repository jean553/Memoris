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
 * @file SerieEditorController.hpp
 * @package controllers
 * @brief render the serie editor
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_SERIEEDITORCONTROLLER_H_
#define MEMORIS_SERIEEDITORCONTROLLER_H_

#include "Controller.hpp"

namespace memoris
{
namespace controllers
{

class SerieEditorController : public Controller
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     */
    SerieEditorController(const utils::Context& context);

    /**
     * @bried default destructor
     */
    ~SerieEditorController();

    /**
     * @brief render the serie editor controller
     *
     * @return const unsigned short&
     */
    virtual const ControllerId& render() const & override;

    /**
     * @brief save the selected levels into a dedicated serie file
     *
     * @param name the name of the serie to create
     *
     * @throw std::ios_base::failure thrown if the file manipulation failed;
     * this exception is never caught by the program and the game directly
     * stops
     */
    void saveSerieFile(const std::string& name) const &;

private:

    /**
     * @brief renders the main components of the controller without foregrounds
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void renderControllerMainComponents() const &;

    /**
     * @brief handles the events of the new serie foreground
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void handleNewSerieForegroundEvents() const &;

    /**
     * @brief handles the events of the save serie foreground
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void handleSaveSerieForegroundEvents() const &;

    /**
     * @brief handles the controller main components events without foregrounds
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void handleControllerEvents() const &;

    /**
     * @brief marks the serie as unsaved by adding an asterisk after the name
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void markSerieUnsaved() const &;

    /**
     * @brief updates the serie name position according to the text width
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateSerieNamePosition() const &;

    /**
     * @brief empty the serie levels list, reload all the available levels
     * into the levels list
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void resetLevelsLists() const &;

    /**
     * @brief set the displayed serie name
     *
     * @param name the name of the serie
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateSerieName(const std::string& name) const &;

    /**
     * @brief loads the new serie foreground
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void openNewSerieForeground() const &;

    /**
     * @brief loads the save serie foreground
     *
     * this code part has been refactored into the function
     * only for organization purposes
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void openSaveSerieForeground() const &;

    class Impl;
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
