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
 * Game interface.
 *
 * @file GameController.hpp
 * @brief main controller for the game
 * @package controllers
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef DEF_GAME_CONTROLLER
#define DEF_GAME_CONTROLLER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Controller.hpp"
#include "Level.hpp"

namespace controllers
{
class GameController : public Controller
{
public:

    GameController();

    /**
     * @brief renders the game main screen
     *
     * @param pContext commons items for controller
     *
     * @return short    id of the new screen controller
     */
    unsigned short render(utils::Context* pContext);

private:

    /**
     * @brief tries to move the player in the given direction
     * only if the status of the game is playing
     *
     * @param direction specific direction
     */
    void movePlayer(PlayerDirection direction);

    /**
     * @brief checks the new player cell, trigger event according to this cell
     */
    void executeCellAction();

    /**
     * @brief display the game time
     *
     * @param pContext pointer to the current context
     */
    void displayTime(utils::Context* ctx);

    /**
     * @brief set and increment the displayed value of the star counter
     */
    void updateStarCntStr();

    /**
     * @brief update the time string according to the current time
     */
    std::string updateTimeStr();

    /**
     * @brief update the lifes string according to the lifes amount
     */
    void updateLifesCntStr();

    /**
     * @brief set and increment the displayed value of the watching time counter
     */
    void updateWatchingTimeStr();

    /* do not use a const for casting problems with getElapsedTime().asMilliseconds() */
    /* TODO: should be const ? */
    static int32_t DEFAULT_WATCHING_TIME;

    /* interval to wait before changing the game time value */
    static const uint8_t TIMER_ITRVL;
    static const uint8_t WATCH_TIME_INCREMENTATION;

    static const std::string TEMPORARY_DEFAULT_LEVEL;
    static const std::string STAR_IMG_PATH;
    static const std::string LIFE_IMG_PATH;
    static const std::string TOTAL_STARS_IMG_PATH;
    static const std::string TIME_IMG_PATH;
    static const std::string FLOOR_IMG_PATH;

    static const float_t LEVEL_HORIZONTAL_POSITION;
    static const float_t LEVEL_VERTICAL_POSITION;

    static const uint16_t TIMER_HRTL_PSTN;
    static const uint16_t TIMER_VRTL_PSTN;
    static const uint16_t STAR_HRTL_PSTN;
    static const uint16_t STAR_VRTL_PSTN;
    static const uint16_t LIFE_HRTL_PSTN;
    static const uint16_t LIFE_VRTL_PSTN;
    static const uint16_t FOUND_STAR_CELLS_HRTL_PSTN;
    static const int16_t FOUND_STAR_CELLS_VRTL_PSTN;
    static const uint16_t LIFES_HRTL_PSTN;
    static const uint16_t LIFES_VRTL_PSTN;

    static const float_t TOTAL_STARS_HRTL_PSTN;
    static const float_t TOTAL_STARS_VRTL_PSTN;
    static const float_t TARGET_HRTL_PSTN;
    static const float_t TARGET_VRTL_PSTN;
    static const float_t TIME_HRTL_PSTN;
    static const float_t TIME_VRTL_PSTN;
    static const float_t TIME_IMG_HRTL_PSTN;
    static const float_t TIME_IMG_VRTL_PSTN;
    static const float_t LEFT_SEPARATOR_PSTN;
    static const float_t RIGHT_SEPARATOR_PSTN;
    static const float_t FLOOR_HRTL_PSTN;
    static const float_t FLOOR_VRTL_PSTN;
    static const float_t FLOOR_IMG_HRTL_PSTN;
    static const float_t FLOOR_IMG_VRTL_PSTN;

    /**
     * @enum GameController::GameStatus
     *
     * @brief gives information about the current status of the game
     */
    enum GameStatus
    {
        WATCHING, /* < the player is watching the level before playing */
        PLAYING /* < the player is playing the level and moving over the cells */
    };

    uint16_t starCellsAmount;
    uint16_t foundStarCellsAmount;
    uint16_t lifesAmount;

    uint8_t timeMilli;
    uint8_t timeSec;
    uint8_t timeMin;
    uint8_t floor;
    uint8_t watchTime;

    bool terminateGame;

    GameStatus status;

    entities::Level level;

    sf::Clock clock;
    sf::Clock timeClck;

    sf::SoundBuffer soundBuffer;

    sf::Sound soundHideLevel;

    sf::Text time;
    sf::Text foundStarsAmntStr;
    sf::Text lifesAmntStr;
    sf::Text targetStr;
    sf::Text timeStr;
    sf::Text floorStr;

    sf::Font fontTime;
    sf::Font fontItems;

    sf::Color colorItems;

    sf::Texture textureStar;
    sf::Texture textureLife;
    sf::Texture textureTarget;
    sf::Texture textureTime;
    sf::Texture textureFloor;

    sf::Sprite spriteStar;
    sf::Sprite spriteLife;
    sf::Sprite spriteTarget;
    sf::Sprite spriteTime;
    sf::Sprite spriteFloor;

    sf::RectangleShape leftSeparator;
    sf::RectangleShape rightSeparator;
};
}

#endif
