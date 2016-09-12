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
#include "GameManager.hpp"

#include <SFML/Audio/Music.hpp>
#include <SFML/System/Clock.hpp>

/* TODO: delete this huge inclusion, only here because each object depends
   of the context includes; to delete after whole refactoring of includes
   in every headers */
#include <SFML/Graphics.hpp>

namespace memoris
{
namespace utils
{

class Context : public utils::NotCopiable
{

public:

    /**
     * @brief constructor, create and set the SFML window, initializes the
     * resources managers
     *
     * @throw std::invalid_argument a texture resource or a font resource
     * cannot be loaded correctly; the exception is never caught in order to
     * stop the program
     */
    Context();

    /* getters of the resources managers; return constant references, as the
       managers objects are unique in the whole application */

    /**
     * @brief getter of the textures manager
     *
     * @return const textures::TexturesManager&
     */
    const managers::TexturesManager& getTexturesManager() const & noexcept;

    /**
     * @brief getter of the sounds manager
     *
     * @return const sounds::SoundsManager&
     */
    const managers::SoundsManager& getSoundsManager() const & noexcept;

    /**
     * @brief getter of the colors manager
     *
     * @return const colors::ColorsManager&
     */
    const managers::ColorsManager& getColorsManager() const & noexcept;

    /**
     * @brief getter of the fonts manager
     *
     * @return const fonts::FontsManager&
     */
    const managers::FontsManager& getFontsManager() const & noexcept;

    /**
     * @brief getter of the cells textures manager
     *
     * @return const textures::CellsTexturesManager&
     */
    const managers::CellsTexturesManager& getCellsTexturesManager() const &
    noexcept;

    /**
     * @brief getter of the playing serie manager
     *
     * @return series::PlayingSerieManager&
     *
     * do not return a constant reference, the manager is modified when
     * a new serie is loaded by OfficialSeriesMenuController when calling
     * loadSerieFileContent()
     *
     * not constant method because returns a reference
     */
    managers::PlayingSerieManager& getPlayingSerieManager() & noexcept;

    /**
     * @brief getter of the game manager
     *
     * @return managers::GameManager&
     *
     * do not return a constant reference, the manager is modified when
     * a new game is created or when an existing game is loaded
     *
     * not constant method because returns a reference
     */
    managers::GameManager& getGameManager() & noexcept;

    /**
     * @brief getter on the SFML window object
     *
     * @return sf::RenderWindow&
     *
     * do not return a constant reference, the SFML window object draw()
     * method is called almost everywhere in the game, and this method
     * is not constant
     *
     * not constant method because returns a reference
     */
    sf::RenderWindow& getSfmlWindow() & noexcept;

    /* method to get SFML time; return a copy of the concerned value */

    /**
     * @brief return the elapsed time in milliseconds since
     * the clock started or restarted; returns a SFML integer
     * type for 32 bits integer; the maximum value is equivalent
     * to 49 days; we can considere that this "case won't never
     * happen"
     *
     * @return const sf::Int32
     *
     * do not return a reference because returns a temporary rvalue from the
     * SFML function getElapsedTime().asMilliseconds()
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    const sf::Int32 getClockMillisecondsTime() const &;

    /* public methods that affect the current object instance */

    /**
     * @brief load a new music file and play it,
     * silently fails if the music cannot be loaded
     *
     * @param path file path of the music to play
     *
     * not constant method because it calls SFML openFromFile() which is not
     * constant
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void loadMusicFile(const std::string& path) &;

    /**
     * @brief check if a music is playing, if yes, stop it
     *
     * not constant method because it calls SFML stop() which is not constant
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void stopMusic() &;

    /**
     * @brief restart the SFML clock; this function is called
     * everytime the screen is switched from one controller
     * to another
     *
     * not constant method because SFML restart() is not constant
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void restartClock() &;

private:

    /* resources and assets managers */

    managers::TexturesManager texturesManager;
    managers::SoundsManager soundsManager;
    managers::ColorsManager colorsManager;
    managers::FontsManager fontsManager;
    managers::CellsTexturesManager cellsTexturesManager;
    managers::GameManager gameManager;
    managers::PlayingSerieManager playingSerieManager;

    /* main SFML window object */
    sf::RenderWindow sfmlWindow;

    /* SFML music to play */
    sf::Music music;

    /* unique SFML clock for time management in every controller
     *
     * NOTE: we use an unique clock for all the animation and time
     * management of the game; the clock is restarted everytime the
     * controller is modified; the maximum time returned in milliseconds
     * is equal to 49 days... so this is a safe method */
    sf::Clock clock;
};

}
}

#endif
