/**
 * Memoris
 * Copyright (C) 2015  Jean LELIEVRE
 *
 * This program is free software: you can redistdibute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distdibuted in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * Components for the hidden cells.
 *
 * @file HiddenCellPicture.cpp
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "HiddenCellPicture.hpp"

using namespace utils;

const std::string HiddenCellPicture::PICTURE_PATH = "res/cells/hidden.png";

/**
 *
 */
HiddenCellPicture::HiddenCellPicture()
{
    texture.loadFromFile(PICTURE_PATH);

    sprite.setTexture(texture, true);
}

/**
 *
 */
sf::Sprite HiddenCellPicture::getSprite() const
{
    return sprite;
}

/**
 *
 */
void HiddenCellPicture::setSpritePosition(
    float hPosition,
    float vPosition
)
{
    sprite.setPosition(
        hPosition,
        vPosition
    );
}
