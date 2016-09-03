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

#include "Context.hpp"

namespace memoris
{
namespace popups
{

class Dialog
{

public:

    /**
     * @brief render the dialog window
     *
     * @param context shared pointer to the current context to use
     */
    virtual void render(const std::shared_ptr<utils::Context>& context) = 0;

protected:

    /**
     * @brief constructor, initializes all the dialog SFML surfaces
     *
     * @param context shared pointer to the current context
     * @param hSize horizontal size of the dialog window
     * @param vSize vertical size of the dialog window
     * @param hPosition horizontal position of the dialog window
     * @param vPosition vertical position of the dialog window
     * @param text dialog window title
     */
    Dialog(
        const std::shared_ptr<utils::Context>& context,
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
     * @param context shared pointer to the current context to use
     */
    void displayParentContent(
        const std::shared_ptr<utils::Context>& context
    ) const;

private:

    /* the SFML surface of the background */
    sf::RectangleShape background;

    /* the SFML surfaces of the borders */
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    /* the SFML surfaces specific to a dialog popup */
    sf::RectangleShape titleBackground;
    sf::RectangleShape titleSeparator;

    /* the dialog title */
    sf::Text title;
};

}
}

#endif
