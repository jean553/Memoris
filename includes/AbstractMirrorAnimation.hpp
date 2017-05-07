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
 * @file AbstractMirrorAnimation.hpp
 * @brief abstract class that manages the level mirror animations
 * @package animations
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_ABSTRACTMIRRORANIMATION_H_
#define MEMORIS_ABSTRACTMIRRORANIMATION_H_

#include "LevelAnimation.hpp"

namespace sf
{
/* 'typedef unsigned int Uint8' in SFML/Config.hpp, we declare exactly
   the same type here in order to both use declaration forwarding and
   prevent conflicting declaration */
typedef unsigned char Uint8;
}

namespace memoris
{
namespace animations
{

class AbstractMirrorAnimation : public LevelAnimation
{

public:

    /**
     * @brief default destructor
     */
    ~AbstractMirrorAnimation();

protected:

    /**
     * @brief constructor
     *
     * @param context the context to use
     * @param level the level of the animation
     */
    AbstractMirrorAnimation(
        const utils::Context& context,
        const std::shared_ptr<entities::Level>& level
    );

    /**
     * @brief increases the transparency
     */
    void increaseTransparency() const & noexcept;

    /**
     * @brief increases the transparency
     */
    void decreaseTransparency() const & noexcept;

    /**
     * @brief set the transparency to fully transparent
     */
    void setFullTransparent() const & noexcept;

    /**
     * @brief set the transparency to no transparent
     */
    void setNoTransparent() const & noexcept;

    /**
     * @brief applies the current animated side transparency on the given cell
     *
     * not noexcept because it calls SFML methods that are not noexcept
     */
    void applyTransparencyOnOneCell(const unsigned short& index) const &;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
