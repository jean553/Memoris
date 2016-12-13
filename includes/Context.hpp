/**
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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

#include <SFML/Config.hpp>

#include <memory>

namespace sf
{
class RenderWindow;
}

namespace memoris
{

namespace managers
{
class TexturesManager;
class SoundsManager;
class ColorsManager;
class FontsManager;
class CellsTexturesManager;
class ShapesManager;
class PlayingSerieManager;
class EditingLevelManager;
}

namespace entities
{
class Game;
}

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

    /**
     * @brief default destructor, empty, declared in order to use the
     * forwarding declaration
     */
    ~Context() noexcept;

    /* getters of the resources managers; they all return constant references,
       the managers are never directly modified by the controllers */

    /**
     * @brief getter of the textures manager
     *
     * @return const managers::TexturesManager&
     */
    const managers::TexturesManager& getTexturesManager() const & noexcept;

    /**
     * @brief getter of the sounds manager
     *
     * @return const managers::SoundsManager&
     */
    const managers::SoundsManager& getSoundsManager() const & noexcept;

    /**
     * @brief getter of the colors manager
     *
     * @return const managers::ColorsManager&
     */
    const managers::ColorsManager& getColorsManager() const & noexcept;

    /**
     * @brief getter of the fonts manager
     *
     * @return const managers::FontsManager&
     */
    const managers::FontsManager& getFontsManager() const & noexcept;

    /**
     * @brief getter of the cells textures manager
     *
     * @return const managers::CellsTexturesManager&
     */
    const managers::CellsTexturesManager& getCellsTexturesManager() const &
    noexcept;

    /**
     * @brief getter of the cells shapes manager
     *
     * @return const managers::ShapesManager&
     */
    const managers::ShapesManager& getShapesManager() const &
    noexcept;

    /**
     * @brief getter of the playing serie manager
     *
     * @return manager::PlayingSerieManager&
     *
     * do not return a constant reference, the manager is modified when
     * a new serie is loaded by OfficialSeriesMenuController when calling
     * loadSerieFileContent()
     */
    managers::PlayingSerieManager& getPlayingSerieManager() const & noexcept;

    /**
     * @brief getter of the editing level manager
     *
     * @return manager::EditingLevelManager&
     *
     * do not return a constant reference, the manager attributes are modified
     * when a level file is opened from the editing level controller
     */
    managers::EditingLevelManager& getEditingLevelManager() const & noexcept;

    /**
     * @brief getter on the SFML window object
     *
     * @return sf::RenderWindow&
     *
     * do not return a constant reference, the SFML window object draw()
     * method is called almost everywhere in the game, and this method
     * is not constant
     */
    sf::RenderWindow& getSfmlWindow() const & noexcept;

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
     * do not return a reference because returns a temporary value from the
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
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void loadMusicFile(const std::string& path) const &;

    /**
     * @brief check if a music is playing, if yes, stop it
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void stopMusic() const &;

    /**
     * @brief restart the SFML clock; this function is called
     * everytime the screen is switched from one controller
     * to another
     *
     * no 'noexcept' because the method calls other functions that are not
     * declared as noexcept
     */
    void restartClock() const &;

    /**
     * @brief getter of the game entity
     *
     * @return const entities::Game&
     */
    const entities::Game& getGame() const & noexcept;

private:

    class Impl;
    std::unique_ptr<Impl> impl;
};

}
}

#endif
