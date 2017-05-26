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
     * @brief constructor, just used to transfer parameter
     *
     * @param context constant reference to the current context to use
     */
    SerieEditorController(const utils::Context& context);

    /**
     * @bried default destructor, empty, only declared in order to use
     * forwarding declaration
     */
    ~SerieEditorController() noexcept;

    /**
     * @brief render the serie editor controller
     *
     * @return const unsigned short&
     *
     * the context reference is not constant because this is a virtual method
     * and some definitions have to modify the context attributes
     */
    virtual const ControllerId& render() const & override;

    /**
     * @brief save the current serie file according to the given serie name
     * and the levels of the serie levels list
     *
     * @param name the name of the level to create
     *
     * @throw std::ios_base::failure thrown if the file manipulation failed;
     * this exception is never caught by the program and the game directly
     * stops
     */
    void saveSerieFile(const std::string& name) const &;

private:

    /**
     * @brief add a star at the end of the serie name; we created this method
     * in order to refactor this feature code, required at different locations
     * into the script
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void markSerieUnsaved() const &;

    /**
     * @brief updates the serie name position according to the width of the
     * surface; this method has been created in order to handle the same
     * feature at different locations in the script
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void updateSerieNamePosition() const &;

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
