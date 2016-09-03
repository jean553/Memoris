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
 * @file dialogs.hpp
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "dialogs.hpp"

#include "SaveLevelDialog.hpp"

namespace memoris
{
namespace popups
{

/**
 *
 */
std::unique_ptr<popups::Dialog> getDialogById(
    const std::shared_ptr<utils::Context>& context,
    const unsigned short& id
)
{
    switch(id)
    {
    case SAVE_LEVEL_POPUP_ID:
    {
        return std::make_unique<SaveLevelDialog>(
            context,
            400.f,
            300.f,
            40.f,
            40.f,
            "Save level"
        );
    }
    }

    /* TODO: to delete, this should never be called, this is only to keep
       the logic of the factory function (always return something) and no
       useless variables */
    return nullptr;
}

}
}
