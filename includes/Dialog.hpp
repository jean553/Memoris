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
 * @file Dialog.hpp
 * @brief abstract parent class of all the dialog windows
 * @package popups
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_DIALOG_H_
#define MEMORIS_DIALOG_H_

#include <memory>

namespace memoris
{

namespace widgets
{
class InputTextWidget;
}

namespace utils
{
class Context;
}

namespace popups
{

class Dialog
{

public:

    /**
     * @brief render the dialog window
     *
     * @param context reference to the current context to use
     *
     * not 'const' because implementation could modify the current dialog
     * attributes
     *
     * not 'noexcept' because it calls the SFML functions that are not
     * 'noexcept'
     */
    virtual void render(utils::Context& context) & = 0;

    /**
     * @brief default destructor, empty, declared for forwarding declaration
     */
    ~Dialog() noexcept;

protected:

    /**
     * @brief constructor, initializes all the dialog SFML surfaces
     *
     * @param context reference to the current context
     * @param hSize horizontal size of the dialog window
     * @param vSize vertical size of the dialog window
     * @param hPosition horizontal position of the dialog window
     * @param vPosition vertical position of the dialog window
     * @param text dialog window title
     *
     * 'protected' visibility because it can only be called by child object
     */
    Dialog(
        utils::Context& context,
        const float& hSize,
        const float& vSize,
        const float& hPosition,
        const float& vPosition,
        const std::string& text
    );

    /**
     * @brief called by the child function, display all the basic surfaces
     * of the dialog window
     *
     * @param context reference to the current context to use
     *
     * the context reference is not 'const' because the SFML window draw()
     * method is called from this function; the draw method is not constant
     *
     * 'protected' visibility because it is supposed to be called by child
     * object only
     *
     * no 'noexcept' because it calls the SFML window draw() method which is
     * not noexcept
     */
    void displayParentContent(utils::Context& context) const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
