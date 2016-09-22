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
 * @file TutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TutorialFrame.hpp"

namespace memoris
{
namespace widgets
{

class TutorialFrame::Impl
{

public:

    Impl(
        const float& frameVerticalPosition,
        const float& frameWidth,
        const float& frameHeight
    ) noexcept : 
        verticalPosition(frameVerticalPosition),
        width(frameWidth),
        height(frameHeight)
    {
    }

    float verticalPosition;
    float width;
    float height;
};

/**
 *
 */
TutorialFrame::TutorialFrame(
    const float& frameVerticalPosition,
    const float& frameWidth,
    const float& frameHeight
) noexcept :
    impl(
        std::make_unique<Impl>(
            frameVerticalPosition,
            frameWidth,
            frameHeight
        )
    )
{
}

/**
 *
 */
TutorialFrame::~TutorialFrame() noexcept = default;

/**
 *
 */
const float& TutorialFrame::getVerticalPosition() const & noexcept
{
    return impl->verticalPosition;
}

/**
 *
 */
const float& TutorialFrame::getWidth() const & noexcept
{
    return impl->width;
}

/**
 *
 */
const float& TutorialFrame::getHeight() const & noexcept
{
    return impl->height;
}

}
}
