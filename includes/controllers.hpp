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
 * @brief factory to generate the controllers by ids
 * @file controllers.hpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTROLLERS_H_
#define MEMORIS_CONTROLLERS_H_

#include <memory>

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

class Controller;
enum class ControllerId;

/**
 * @brief returns a pointer to the created controller according to the given id
 *
 * @param context the context to use
 * @param id the controller id
 * @param previousControllerId previous controller id (for error controller)
 *
 * @return std::unique_ptr<Controller>
 */
std::unique_ptr<Controller> getControllerById(
    const utils::Context& context,
    const ControllerId& id,
    const ControllerId& previousControllerId
);

}
}

#endif
