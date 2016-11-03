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

#include "fonts.hpp"
#include "Context.hpp"
#include "FontsManager.hpp"
#include "ColorsManager.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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

    /* vector container because there are many different items on a frame:
       it makes items handling easier; unique pointers because we want use
       polymorphism (sf::Text or sf::Sprite) stored here, and because we
       use move sementics to create them in a dedicated container and insert
       them here in the parent class without copy */
    std::vector<std::unique_ptr<sf::Drawable>> items;
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

/**
 *
 */
void TutorialFrame::applyPropertiesToText(
    const utils::Context& context,
    const std::unique_ptr<sf::Text>& text
)
{
    text->setCharacterSize(fonts::TUTORIAL_SIZE);
    text->setFont(context.getFontsManager().getTutorialFont());
    text->setColor(context.getColorsManager().getColorWhite());
}

/**
 *
 */
void TutorialFrame::insertItem(std::unique_ptr<sf::Drawable> item) &
{
    impl->items.push_back(std::move(item));
}

/**
 *
 */
void TutorialFrame::render(const utils::Context& context) const &
{
    for(auto& item : impl->items) // item -> std::unique_ptr<sf::Drawable>&
    {
        context.getSfmlWindow().draw(*item);
    }
}

}
}
