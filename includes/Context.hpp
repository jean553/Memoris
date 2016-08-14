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
 * @file Context.hpp
 * @brief class for the unique context object of the program, contains data
 * supposed to be transfered from one controller to another
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTEXT_H_
#define MEMORIS_CONTEXT_H_

#include "NotCopiable.hpp"

#include "TexturesManager.hpp"
#include "SoundsManager.hpp"
#include "ColorsManager.hpp"
#include "FontsManager.hpp"
#include "CellsTexturesManager.hpp"
#include "PlayingSerieManager.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <map>
#include <memory>

namespace memoris
{
namespace utils
{

class Context : public others::NotCopiable
{
public:

    /**
     * @brief constructor, create and set the SFML window
     */
    Context();

    /**
     * @brief getter on the SFML window object
     *
     * @return reference to the SFML window object
     */
    sf::RenderWindow& getSfmlWindow();

    /**
     * @brief load a new music file and play it,
     * silently fails if the music cannot be loaded
     *
     * @param path file path of the music to play
     */
    void loadMusicFile(const std::string& path);

    /**
     * @brief check if a music is playing, if yes, stop it
     */
    void stopMusic();

    /**
     * @brief return the elapsed time in milliseconds since
     * the clock started or restarted; returns a SFML integer
     * type for 32 bits integer; the maximum value is equivalent
     * to 49 days; we can considere that this "case won't never
     * happen"
     *
     * @return sf::Int32
     */
    sf::Int32 getClockMillisecondsTime() const;

    /**
     * @brief restart the SFML clock; this function is called
     * everytime the screen is switched from one controller
     * to another
     */
    void restartClock();

    /**
     * @brief getter of the textures manager
     *
     * @return const textures::TexturesManager&
     */
    const textures::TexturesManager& getTexturesManager() const;

    /**
     * @brief getter of the sounds manager
     *
     * @return const sounds::SoundsManager&
     */
    const sounds::SoundsManager& getSoundsManager() const;

    /**
     * @brief getter of the colors manager
     *
     * @return const colors::ColorsManager&
     */
    const colors::ColorsManager& getColorsManager() const;

    /**
     * @brief getter of the fonts manager
     *
     * @return const fonts::FontsManager&
     */
    const fonts::FontsManager& getFontsManager() const;

    /**
     * @brief getter of the cells textures manager
     *
     * @return const textures::CellsTexturesManager&
     */
    const textures::CellsTexturesManager& getCellsTexturesManager() const;

    /**
     * @brief getter of the playing serie manager
     *
     * @return series::PlayingSerieManager&
     *
     * NOTE: the returned reference is not constant, in fact, the manager is
     * modified by the Level class when a level file is loaded
     */
    series::PlayingSerieManager& getPlayingSerieManager();

private:

    /* textures manager; handles all the textures (not cells textures) */
    textures::TexturesManager texturesManager;

    /* the sounds manager, handles all the sounds */
    sounds::SoundsManager soundsManager;

    /* the colors manager, handles all the SFML colors */
    colors::ColorsManager colorsManager;

    /* the fonts manager, handles all the SFML fonts */
    fonts::FontsManager fontsManager;

    /* the manager for the textures of the cells */
    textures::CellsTexturesManager cellsTexturesManager;

    /* the manager for the playing serie */
    series::PlayingSerieManager playingSerieManager;

    /* the main SFML window object */
    sf::RenderWindow sfmlWindow;

    /* the SFML music to play */
    sf::Music music;

    /* the unique SFML clock for time management in every controller
     * NOTE: we use an unique clock for all the animation and time
     * management of the game; the clock is restarted everytime the
     * controller is modified; the maximum time returned in milliseconds
     * is equal to 49 days... so this is a safe method */
    sf::Clock clock;
};

}
}

#endif
