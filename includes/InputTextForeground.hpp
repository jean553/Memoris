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
 * @file InputTextForeground.hpp
 * @brief contains one text line widget to let the user inputs one level name
 * @package foregrounds
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_INPUTTEXTFOREGROUND_H_
#define MEMORIS_INPUTTEXTFOREGROUND_H_

#include "AbstractForeground.hpp"

#include <memory>

namespace memoris
{

namespace widgets
{
class InputTextWidget;
}

namespace foregrounds
{

class InputTextForeground : public AbstractForeground
{

public:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context constant reference to the context to use
     * @param message constant rvalue reference to the message to display
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    InputTextForeground(
        const utils::Context& context,
        const std::string&& message
    );

    /**
     * @brief default destructor, declared in order to use forwarding
     * declaration
     */
    ~InputTextForeground() noexcept;

    /**
     * @brief renders the foreground in front of the controller screen
     *
     * @param context constant reference to the context to use
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void render(const utils::Context& context) const & override final;

    /**
     * @brief getter of the input text widget that contains the level name
     *
     * @return widgets::InputTextWidget&
     *
     * returned reference is not constant as it is updated in the main event
     * loop
     */
    widgets::InputTextWidget& getInputTextWidget() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
