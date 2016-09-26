/**
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
 * @file Controller.hpp
 * @brief parent class for all controllers
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTROLLER_H_
#define MEMORIS_CONTROLLER_H_

#include <memory>

#include <SFML/Window/Event.hpp>

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

class Controller
{

public:

    /**
     * @brief default destructor, empty, only declared in order to use
     * forwarding declaration and virtual to force children objects destructor
     * call
     */
    virtual ~Controller() noexcept;

    /**
     * @brief pure virtual method to render the controller; this function is
     * called from the main loop to render the current controller
     *
     * @param context shared pointer to the context to use
     *
     * @return const unsigned short&
     *
     * not 'const' because the render() methods contain for sure methods
     * calls that modify the current object
     *
     * not 'noexcept' because the render() methods contain for sure methods
     * calls that may throw exceptions
     */
    virtual const unsigned short& render(
        utils::Context& context
    ) & = 0;

protected:

    /**
     * @brief constructor, initializes the implementation
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    Controller(const utils::Context& context);

    /**
     * @brief render the controller switching animation (the animation that
     * is rendered when one screen is closed and a new one is opened, also
     * rendered when the first screen is opened and when the last screen is
     * closed); starts to animate when the expectedControllerId protected
     * value is updated inside the current controller (usually when a menu
     * item is selected, an event occured or a button is pressed); the function
     * returns 0 as long as no animation is rendering or when the animation is
     * rendering; the function returns the expectedControllerId when the
     * animation (opening or closing) is terminated; this id can be stored
     * in the nextControllerId and the screen can be switched.
     *
     * @param context reference to the current context to use
     *
     * @return const unsigned short
     *
     * does not return a reference because the function can directly return
     * a value using return; in some cases
     *
     * not 'const' because it modifies some attributes of the current 
     * controller
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    const unsigned short animateScreenTransition(
        utils::Context& context
    ) &;

    /* TODO: #784 not included in the implementation because used by the
       children objects, this should be refactored */
    unsigned short nextControllerId {0}, expectedControllerId {0};
    sf::Event event;

private:

    static constexpr sf::Uint32 TRANSITION_ANIMATION_INTERVAL {25};
    static constexpr sf::Uint8 COLOR_UPDATE_STEP {51};
    static constexpr sf::Uint8 TRANSITION_STEPS_MAX {5};

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
