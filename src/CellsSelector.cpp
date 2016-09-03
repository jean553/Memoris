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
 * @file CellsSelector.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "CellsSelector.hpp"

#include "cells.hpp"

namespace memoris
{
namespace utils
{

/**
 *
 */
CellsSelector::CellsSelector(const std::shared_ptr<utils::Context>& context)
{
    /* load the SFML textures and set them as sprite textures */

    emptyCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::EMPTY_CELL
        )
    );
    departureCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::DEPARTURE_CELL
        )
    );
    arrivalCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::ARRIVAL_CELL
        )
    );
    starCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAR_CELL
        )
    );
    moreLifeCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::MORE_LIFE_CELL
        )
    );
    lessLifeCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LESS_LIFE_CELL
        )
    );
    moreTimeCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::MORE_TIME_CELL
        )
    );
    lessTimeCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LESS_TIME_CELL
        )
    );
    wallCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::WALL_CELL
        )
    );
    stairsUpCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAIRS_UP_CELL
        )
    );
    stairsDownCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::STAIRS_DOWN_CELL
        )
    );
    horizontalMirrorCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::HORIZONTAL_MIRROR_CELL
        )
    );
    verticalMirrorCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::VERTICAL_MIRROR_CELL
        )
    );
    leftRotationCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::LEFT_ROTATION_CELL
        )
    );
    rightRotationCell.setTexture(
        context->getCellsTexturesManager().getTextureReferenceByCellType(
            cells::RIGHT_ROTATION_CELL
        )
    );

    /* set the sprites positions */

    emptyCell.setPosition(
        320.f,
        98.f
    );

    departureCell.setPosition(
        320.f,
        148.f
    );

    arrivalCell.setPosition(
        320.f,
        198.f
    );

    starCell.setPosition(
        320.f,
        248.f
    );

    moreLifeCell.setPosition(
        320.f,
        298.f
    );

    lessLifeCell.setPosition(
        320.f,
        348.f
    );

    moreTimeCell.setPosition(
        320.f,
        398.f
    );

    lessTimeCell.setPosition(
        320.f,
        448.f
    );

    wallCell.setPosition(
        320.f,
        498.f
    );

    stairsUpCell.setPosition(
        320.f,
        548.f
    );

    stairsDownCell.setPosition(
        320.f,
        598.f
    );

    horizontalMirrorCell.setPosition(
        320.f,
        648.f
    );

    verticalMirrorCell.setPosition(
        320.f,
        698.f
    );

    leftRotationCell.setPosition(
        320.f,
        748.f
    );

    rightRotationCell.setPosition(
        320.f,
        798.f
    );
}

/**
 *
 */
void CellsSelector::display(const std::shared_ptr<utils::Context>& context)
{
    context->getSfmlWindow().draw(emptyCell);
    context->getSfmlWindow().draw(departureCell);
    context->getSfmlWindow().draw(arrivalCell);
    context->getSfmlWindow().draw(starCell);
    context->getSfmlWindow().draw(moreLifeCell);
    context->getSfmlWindow().draw(lessLifeCell);
    context->getSfmlWindow().draw(moreTimeCell);
    context->getSfmlWindow().draw(lessTimeCell);
    context->getSfmlWindow().draw(wallCell);
    context->getSfmlWindow().draw(stairsUpCell);
    context->getSfmlWindow().draw(stairsDownCell);
    context->getSfmlWindow().draw(horizontalMirrorCell);
    context->getSfmlWindow().draw(verticalMirrorCell);
    context->getSfmlWindow().draw(leftRotationCell);
    context->getSfmlWindow().draw(rightRotationCell);
}

}
}
