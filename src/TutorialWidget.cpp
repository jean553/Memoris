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
 * @file TutorialWidget.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "TutorialWidget.hpp"

#include "TutorialFrame.hpp"
#include "Context.hpp"
#include "tutorial_frames.hpp"
#include "ColorsManager.hpp"
#include "PlayingSerieManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <queue>

namespace memoris
{
namespace widgets
{

class TutorialWidget::Impl
{

public:

    Impl(utils::Context& context)
    {
        back.setFillColor(context.getColorsManager().getColorBlueLowAlpha());
        top.setFillColor(context.getColorsManager().getColorWhite());
        left.setFillColor(context.getColorsManager().getColorWhite());
        right.setFillColor(context.getColorsManager().getColorWhite());
        bottom.setFillColor(context.getColorsManager().getColorWhite());

        utils::attachFramesToTutorial(
            context,
            frames,
            context.getPlayingSerieManager().getLevelIndex()
        );
    }

    sf::RectangleShape back;
    sf::RectangleShape top;
    sf::RectangleShape bottom;
    sf::RectangleShape left;
    sf::RectangleShape right;

    sf::Uint32 lastFlashAnimationTime {0};
    sf::Uint32 lastUpdateDimensionAnimationTime {0};

    FlashingColors flashingColor {FlashingColors::WHITE};

    /* we use a queue to store the frames because each frame is only loaded
       one time and displayed one time; once displayed, the frame can be free
       from memory; we store pointers to use polymorphism here (parent abstract
       class TutorialFrame, but each frame is created using a specific class)*/
    std::queue<std::unique_ptr<widgets::TutorialFrame>> frames;

    /* we use an unique pointer for the current frame because each frame is
       popped from the queue and moved using move sementics inside this current
       frame pointer; the memory is dynamically managed and it could be any
       kind of tutorial frame child (polymorphism) */
    std::unique_ptr<widgets::TutorialFrame> currentFrame;

    bool animated {false};
};

/**
 *
 */
TutorialWidget::TutorialWidget(utils::Context& context) :
    impl(std::make_unique<Impl>(context))
{
    /* directly force to pop the first item of the queue */
    loadFrame();

    updateWidgetDimensions(
        impl->currentFrame->getWidth(),
        impl->currentFrame->getHeight(),
        impl->currentFrame->getVerticalPosition()
    );
}

/**
 *
 */
TutorialWidget::~TutorialWidget() noexcept = default;

/**
 *
 */
void TutorialWidget::display(utils::Context& context) &
{
    animateFlashingAnimation(context);

    if (impl->animated)
    {
        animateDimensions(context);
    }

    context.getSfmlWindow().draw(impl->back);
    context.getSfmlWindow().draw(impl->top);
    context.getSfmlWindow().draw(impl->bottom);
    context.getSfmlWindow().draw(impl->left);
    context.getSfmlWindow().draw(impl->right);

    /* two times the same conditional test in the same method; we have no
       choice anyway to render the frame after the background */
    if (!impl->animated)
    {
        impl->currentFrame->render(context);
    }
}

/**
 *
 */
const bool TutorialWidget::nextFrame() &
{
    if (impl->frames.empty())
    {
        return false;
    }

    impl->animated = true;

    loadFrame();

    return true;
}

/**
 *
 */
void TutorialWidget::animateFlashingAnimation(utils::Context& context) &
{
    if (
        context.getClockMillisecondsTime() -
        impl->lastFlashAnimationTime < 500
    )
    {
        return;
    }

    if (impl->flashingColor == FlashingColors::BLUE)
    {
        setBorderColor(context.getColorsManager().getColorWhite());
        impl->flashingColor = FlashingColors::WHITE;
    }
    else
    {
        setBorderColor(context.getColorsManager().getColorBlue());
        impl->flashingColor = FlashingColors::BLUE;
    }

    impl->lastFlashAnimationTime = context.getClockMillisecondsTime();
}

/**
 *
 */
void TutorialWidget::setBorderColor(const sf::Color& color) &
{
    impl->top.setFillColor(color);
    impl->left.setFillColor(color);
    impl->right.setFillColor(color);
    impl->bottom.setFillColor(color);
}

/**
 *
 */
void TutorialWidget::updateWidgetDimensions(
    const float& width,
    const float& height,
    const float& position
) &
{
    impl->back.setSize(
        sf::Vector2f(
            width,
            height
        )
    );

    impl->top.setSize(
        sf::Vector2f(
            width,
            BORDER_WIDTH
        )
    );

    impl->bottom.setSize(
        sf::Vector2f(
            width,
            BORDER_WIDTH
        )
    );

    impl->left.setSize(
        sf::Vector2f(
            BORDER_WIDTH,
            height
        )
    );

    impl->right.setSize(
        sf::Vector2f(
            BORDER_WIDTH,
            height
        )
    );

    impl->back.setPosition(
        HORIZONTAL_POSITION,
        impl->currentFrame->getVerticalPosition()
    );

    impl->left.setPosition(
        HORIZONTAL_POSITION,
        impl->currentFrame->getVerticalPosition()
    );

    impl->top.setPosition(
        HORIZONTAL_POSITION,
        impl->currentFrame->getVerticalPosition()
    );

    impl->right.setPosition(
        HORIZONTAL_POSITION + width - 2.f,
        impl->currentFrame->getVerticalPosition()
    );

    impl->bottom.setPosition(
        HORIZONTAL_POSITION,
        impl->currentFrame->getVerticalPosition() +
        height - 2.f
    );
}

/**
 *
 */
void TutorialWidget::animateDimensions(const utils::Context& context) &
{
    if (
        context.getClockMillisecondsTime() -
        impl->lastUpdateDimensionAnimationTime < 50
    )
    {
        return;
    }

    /* these SFML getters do not necessarely return float types */
    float height = static_cast<float>(impl->back.getGlobalBounds().height);
    float width = static_cast<float>(impl->back.getGlobalBounds().width);
    float verticalPosition = static_cast<float>(impl->back.getPosition().y);
    float frameHeight = static_cast<float>(impl->currentFrame->getHeight());
    float frameWidth = static_cast<float>(impl->currentFrame->getWidth());
    float framePosition = static_cast<float>(
        impl->currentFrame->getVerticalPosition()
    );

    if (frameHeight < height)
    {
        height -= DIMENSION_UPDATE_STEP;
    }
    else if (frameHeight > height)
    {
        height += DIMENSION_UPDATE_STEP;
    }

    if (frameWidth < width)
    {
        width -= DIMENSION_UPDATE_STEP;
    }
    else if (frameWidth > width)
    {
        width += DIMENSION_UPDATE_STEP;
    }

    if (framePosition < verticalPosition)
    {
        verticalPosition -= DIMENSION_UPDATE_STEP;
    }
    else if (framePosition > verticalPosition)
    {
        verticalPosition += DIMENSION_UPDATE_STEP;
    }

    updateWidgetDimensions(
        width,
        height,
        verticalPosition
    );

    if (
        height == frameHeight and
        width == frameWidth and
        verticalPosition == framePosition
    )
    {
        impl->animated = false;
    }

    impl->lastUpdateDimensionAnimationTime =
    context.getClockMillisecondsTime();
}

/**
 *
 */
void TutorialWidget::loadFrame() &
{
    impl->currentFrame = std::move(impl->frames.front());
    impl->frames.pop();
}

}
}
