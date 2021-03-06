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
 * @file FilesSelectionListWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "FilesSelectionListWidget.hpp"

#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"
#include "fonts_sizes.hpp"

#include <SFML/Graphics/Text.hpp>

#include <cstring>
#include <stdexcept>
#include <string>

#include <dirent.h> // C library

namespace memoris
{
namespace widgets
{

class FilesSelectionListWidget::Impl
{

public:

    Impl(
        const utils::Context& context,
        const char* directory
    ) :
        context(context),
        directoryPath(directory)
    {
    }

    const utils::Context& context;

    const char* directoryPath;
};

/**
 *
 */
FilesSelectionListWidget::FilesSelectionListWidget(
    const utils::Context& context,
    const char* directory,
    const float& horizontalPosition
) :
    SelectionListWidget(
        context,
        horizontalPosition
    ),
    impl(std::make_unique<Impl>(context, directory))
{
    loadFilesFromDirectory();
}

/**
 *
 */
FilesSelectionListWidget::~FilesSelectionListWidget() = default;

/**
 *
 */
void FilesSelectionListWidget::loadFilesFromDirectory() const & noexcept
{
    /* this function uses a C library (dirent.h), so it also uses old-C++
       coding style (no smart pointer) */

    /* pointer to a custom type of dirent.h used for reading steps */
    struct dirent* reader = NULL;

    /* pointer to the object managing the directory reading */
    DIR* dir = opendir(impl->directoryPath);

    /* NOTE: the code here segfault if the directory cannot be open;
       we voluntary do not handle any exception in order to let
       the program stops */

    while((reader = readdir(dir)) != NULL)
    {
        /* std::string operator= accepts const char* types */
        std::string item = reader->d_name;

        /* remove the file extension from the file name */
        size_t extensionPosition = item.find_last_of(".");
        item = item.substr(0, extensionPosition);

        /* ignore special values */
        if (
            item == ".." ||
            item == "." ||
            item == ""
        )
        {
            continue;
        }

        addItem(std::move(item));
    }

    closedir(dir);
}

}
}
