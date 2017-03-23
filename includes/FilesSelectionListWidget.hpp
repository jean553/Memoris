/*
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
 * @file FilesSelectionListWidget.hpp
 * @brief list files from a directory into a selection list widget
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_FILESSELECTIONLISTWIDGET_H_
#define MEMORIS_FILESSELECTIONLISTWIDGET_H_

#include "SelectionListWidget.hpp"

namespace memoris
{
namespace widgets
{

class FilesSelectionListWidget : public SelectionListWidget
{

public:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param directory path of the directory
     * @param horizontalPosition the expected horizontal position of the widget
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * this exception is never caught and the program terminates
     *
     * @throws std::invalid_argument throws an exception if the directory cannot
     * be open or if an error occures (no matter what the error is); this
     * exception is never caught and the program just stops
     */
    FilesSelectionListWidget(
        const utils::Context& context,
        const char* directory,
        const float& horizontalPosition = 500.f
    );

    FilesSelectionListWidget(const FilesSelectionListWidget&) = delete;

    FilesSelectionListWidget& operator=(const FilesSelectionListWidget&) = delete;

    /**
     * @brief default destructor
     */
    ~FilesSelectionListWidget();

    /**
     * @brief loads filenames from the directory specified by the constructor,
     * the following names are ignored:
     * - the parent directory name,
     * - the current directory name,
     * - empty names 
     * the names are loaded into the sf::Text lists from the parent class
     *
     * @throws std::invalid_argument throws an exception if the directory cannot
     * be open or if an error occures (no matter what the error is); this
     * exception is never caught and the program just stops
     *
     * this method is called directly from the constructor
     * but not directly defined within it;
     * the series editor requires to reload files from levels directory
     */
    void loadFilesFromDirectory() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
