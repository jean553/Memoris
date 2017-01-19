/**
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
 * @file Controller.hpp
 * @brief parent class for all controllers
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTROLLER_H_
#define MEMORIS_CONTROLLER_H_

#include <memory>

namespace sf
{
class Event;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace controllers
{

enum class ControllerId;

class Controller
{

public:

    Controller(const Controller&) = delete;
    Controller& operator=(const Controller&) = delete;

    /**
     * @brief default destructor defined in order to use forwarding
     * declaration and marked as virtual to ensure that every destructors
     * are called during controller destruction as we use polymorphism
     */
    virtual ~Controller();

    /**
     * @brief used to render each controller
     *
     * @return const ControllerId&
     */
    virtual const ControllerId& render() & = 0;

protected:

    /**
     * @brief constructor
     *
     * @param context reference to the current context to use
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    Controller(const utils::Context& context);

    /**
     * @brief plays switch controller (screen) animation
     *
     * @param context constant reference to the current context to use
     *
     * @return const controllers::ControllerId
     *
     * not 'noexcept' because it calls SFML methods that are not noexcept
     */
    const ControllerId animateScreenTransition(
        const utils::Context& context
    ) const &;

    /**
     * @brief returns the next controller id
     *
     * @return const ControllerId&
     */
    const ControllerId& getNextControllerId() const & noexcept;

    /**
     * @brief sets the next controller id
     *
     * @param nextControllerId the next controller id
     */
    void setNextControllerId(const ControllerId& nextControllerId) const & 
        noexcept;

    /**
     * @brief sets the expected controller id
     *
     * @param expectedControllerId the expected controller id
     */
    void setExpectedControllerId(const ControllerId& expectedControllerId)
        const & noexcept;

    /**
     * @brief returns a reference to the controller event
     *
     * @return sf::Event&
     */
    sf::Event& getEvent() const & noexcept;

    /**
     * @brief returns a constant reference to the context
     *
     * @return const utils::Context&
     */
    const utils::Context& getContext() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
