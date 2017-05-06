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
 * @file LevelAnimation.hpp
 * @brief interface for all the level animations
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_LEVELANIMATION_H_
#define MEMORIS_LEVELANIMATION_H_

#include <memory>

namespace sf
{
/* 'typedef unsigned int Uint32' in SFML/Config.hpp, we declare exactly
   the same type here in order to both use declaration forwarding and
   prevent conflicting declaration */
typedef unsigned int Uint32;
}

namespace memoris
{

namespace utils
{
class Context;
}

namespace entities
{
class Level;
}

namespace animations
{

class LevelAnimation
{

public:

    /**
     * @brief constructor
     */
    LevelAnimation();

    /**
     * @brief default destructor
     */
    virtual ~LevelAnimation();

    /**
     * @brief renders the animation, called by the game controller
     *
     * @param context the context to use
     * @param level the level to animate
     * @param floor the current floor to display
     *
     * not const because definitions updates object attributes
     *
     * not noexcept because definitions calls SFML functions that are not
     * noexcept
     */
    virtual void renderAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    ) & = 0;

    /**
     * @brief true if the animation is finished
     *
     * @return const bool&
     */
    const bool& isFinished() const & noexcept;

protected:

    static constexpr unsigned short TOP_SIDE_LAST_CELL_INDEX {128};
    static constexpr unsigned short CELLS_PER_LINE {16};
    static constexpr unsigned short CELLS_PER_FLOOR {256};

    /**
     * @brief hides or shows the given cell at the given index
     *
     * @param context the context to use
     * @param level shared pointer to the concerned level object
     * @param index the index of the cell to display or to hide
     * @param visible boolean that indicates if the cell has to be hide or not
     *
     * not noexcept because it calls SFML functions
     */
    void showOrHideCell(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& index,
        const bool& visible
    ) const &;

    /**
     * @brief increments the animation step
     *
     * @param context the context to use
     *
     * not const because it modifies the animation step attribute
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void incrementAnimationStep(const utils::Context& context) &;

    /**
     * @brief moves the player on a new cell according to the updated player
     * cell index value

     * @param context the context to use
     * @param level the concerned level
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void movePlayer(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level
    ) const &;

    /**
     * @brief getter of the last animation update time
     *
     * @return const sf::Uint32&
     */
    const sf::Uint32& getAnimationLastUpdateTime() const & noexcept;

    /**
     * @brief setter of the last animation update time;
     * used by the stairs animation
     */
    void setAnimationLastUpdateTime(const sf::Uint32& time) const & noexcept;

    /**
     * @brief getter of the animation steps
     *
     * @return const unsigned short&
     */
    const unsigned short& getAnimationSteps() const & noexcept;

    /**
     * @brief set the animation as finished
     */
    void endsAnimation() const & noexcept;

    /**
     * @brief getter of the new player index after animation
     *
     * @return const short&
     */
    const short& getUpdatedPlayerIndex() const & noexcept;

    /**
     * @brief setter of the new player index after animation
     *
     * @param index the new player index after animation
     */
    void setUpdatedPlayerIndex(const short& index) const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
