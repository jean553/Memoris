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
typedef unsigned char Uint8;
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
     *
     * @param context the context to use
     * @param level the level of the animation
     * @param floor the animation floor index
     */
    LevelAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level,
        const unsigned short& floor
    );

    LevelAnimation(const LevelAnimation&) = delete;

    LevelAnimation& operator=(const LevelAnimation&) = delete;

    /**
     * @brief default destructor
     */
    virtual ~LevelAnimation();

    /**
     * @brief renders the animation, called by the game controller
     *
     * not const because definitions updates object attributes
     *
     * not noexcept because definitions calls SFML functions that are not
     * noexcept
     */
    virtual void renderAnimation() & = 0;

    /**
     * @brief true if the animation is finished
     *
     * @return const bool&
     */
    const bool& isFinished() const & noexcept;

protected:

    /**
     * @brief getter of the context
     */
    const utils::Context& getContext() const & noexcept;

    /**
     * @brief getter of the level
     */
    const std::shared_ptr<entities::Level>& getLevel() const & noexcept;

    /**
     * @brief getter of the floor
     */
    const unsigned short& getFloor() const & noexcept;

    /**
     * @brief hides or shows the given cell at the given index
     *
     * @param index the index of the cell to display or to hide
     * @param visible boolean that indicates if the cell has to be hide or not
     * @param transparency optional transparency of the cell
     *
     * NOTE: the transparency is used by some animations when updating
     * the cells textures without immediately displaying it (horizontal
     * mirror animation, vertical mirror animation)
     *
     * not noexcept because it calls SFML functions
     */
    void showOrHideCell(
        const unsigned short& index,
        const bool& visible,
        const sf::Uint8& transparency = 255
    ) const &;

    /**
     * @brief increments the animation step
     *
     * not noexcept because it calls SFML functions that are not noexcept
     */
    void incrementAnimationStep() const &;

    /**
     * @brief moves the player on a new cell according to the updated player
     * cell index value

     * not noexcept because it calls SFML methods that are not noexcept
     */
    void movePlayer() const &;

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
    const std::unique_ptr<Impl> impl;
};

}
}

#endif
