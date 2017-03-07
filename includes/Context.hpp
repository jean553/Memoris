/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @brief unique context, forwarded from one controller to another one
 * @package utils
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_CONTEXT_H_
#define MEMORIS_CONTEXT_H_

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

class Context
{

public:

    /**
     * @brief constructor
     *
     * @throw std::invalid_argument a texture resource or a font resource
     * cannot be loaded; the exception is never caught and the program stops
     *
     * @throw std::bad_alloc the implementation cannot be initialized;
     * the exception is never caught and the program stops
     */
    Context();

    Context(const Context&) = delete;

    Context& operator=(const Context&) = delete;

    /**
     * @brief default destructor
     */
    ~Context();

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
     * the manager is modified when calling loadSerieFileContent()
     */
    managers::PlayingSerieManager& getPlayingSerieManager() const & noexcept;

    /**
     * @brief getter of the editing level manager
     *
     * @return manager::EditingLevelManager&
     *
     * the manager is modified when a level is loaded into the level editor
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

    /**
     * @brief return the elapsed time (milliseconds) since the clock started
     * or restarted (maximum value is 49 days, this behavior is undefined)
     *
     * @return const sf::Int32
     *
     * SFML sf::Clock::getElapsedTime() and sf::Time::asMilliseconds()
     * are not noexcept
     */
    const sf::Int32 getClockMillisecondsTime() const &;

    /**
     * @brief load a new music file and play it,
     * silently fails if the music cannot be loaded
     *
     * @param path file path of the music to play
     *
     * SFML sf::Music::openFromFile(), sf::Music::play() and
     * setLoop() are not noexcept
     */
    void loadMusicFile(const std::string& path) const &;

    /**
     * @brief stop the playing music
     *
     * SFML sf::Music::getStatus() and sf::Music::stop() are not noexcept
     */
    void stopMusic() const &;

    /**
     * @brief restart the SFML clock; this function is called
     * everytime the screen is switched from one controller
     * to another
     *
     * SFML sf::Clock::restart() is not noexcept
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
