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
 * @file MoreLessTimeCellsTutorialFrame.cpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "MoreLessTimeCellsTutorialFrame.hpp"

#include "Context.hpp"
#include "CellsTexturesManager.hpp"
#include "cells.hpp"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace memoris
{
namespace widgets
{

/**
 *
 */
MoreLessTimeCellsTutorialFrame::MoreLessTimeCellsTutorialFrame(
    const utils::Context& context
) :
    TutorialFrame(
        200.f,
        630.f,
        250.f
    )
{
    auto firstLine = std::make_unique<sf::Text>();
    auto secondLine = std::make_unique<sf::Text>();
    auto thirdLine = std::make_unique<sf::Text>();
    auto fourthLine = std::make_unique<sf::Text>();
    auto fifthLine = std::make_unique<sf::Text>();
    auto moreTimeLine = std::make_unique<sf::Text>();
    auto lessTimeLine = std::make_unique<sf::Text>();

    auto moreTimeCell = std::make_unique<sf::Sprite>();
    auto lessTimeCell = std::make_unique<sf::Sprite>();

    moreTimeCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::MORE_TIME_CELL
        )
    );

    lessTimeCell->setTexture(
        context.getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LESS_TIME_CELL
        )
    );

    firstLine->setString(
        "The watching time is transfered from one level to another "
        "one inside the "
    );

    secondLine->setString(
        "same serie. The watching time value depends of the watching "
        "time cells you "
    );

    thirdLine->setString(
        "find during the game. The 'More Time Cell' adds three seconds "
        "of watching time "
    );

    fourthLine->setString(
        "for the next level. The 'Less Time Cell' removes three seconds. "
        "The minimum watching "
    );

    fifthLine->setString(
        "is three seconds."
    );

    moreTimeLine->setString("3 seconds more");
    lessTimeLine->setString("3 seconds less");

    applyPropertiesToText(
        context,
        firstLine
    );

    applyPropertiesToText(
        context,
        secondLine
    );

    applyPropertiesToText(
        context,
        thirdLine
    );

    applyPropertiesToText(
        context,
        fourthLine
    );

    applyPropertiesToText(
        context,
        fifthLine
    );

    applyPropertiesToText(
        context,
        moreTimeLine
    );

    applyPropertiesToText(
        context,
        lessTimeLine
    );

    firstLine->setPosition(
        20.f,
        210.f
    );

    secondLine->setPosition(
        20.f,
        230.f
    );

    thirdLine->setPosition(
        20.f,
        250.f
    );

    fourthLine->setPosition(
        20.f,
        270.f
    );

    fifthLine->setPosition(
        20.f,
        290.f
    );

    moreTimeCell->setPosition(
        200.f,
        350.f
    );

    lessTimeCell->setPosition(
        400.f,
        350.f
    );

    moreTimeLine->setPosition(
        170.f,
        410.f
    );

    lessTimeLine->setPosition(
        370.f,
        410.f
    );

    insertItem(std::move(firstLine));
    insertItem(std::move(secondLine));
    insertItem(std::move(thirdLine));
    insertItem(std::move(fourthLine));
    insertItem(std::move(fifthLine));
    insertItem(std::move(moreTimeCell));
    insertItem(std::move(lessTimeCell));
    insertItem(std::move(lessTimeLine));
    insertItem(std::move(moreTimeLine));
}

}
}
