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
 * @file PlayingSerieManager.hpp
 * @brief singleton object class used to load serie content from file and pass
 * the serie information from one game controller to another during the level
 * switchs
 * TODO: #560 this class is not "as necessary as" the textures manager or the
 * fonts manager; the scope should not be global;
 * @package series
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#ifndef MEMORIS_PLAYINGSERIEMANAGER_H_
#define MEMORIS_PLAYINGSERIEMANAGER_H_

#include "NotCopiable.hpp"

#include <string>
#include <queue>

namespace memoris
{
namespace series
{

class PlayingSerieManager : public others::NotCopiable
{

public:

    /**
     * @brief static variable to get a reference to the instance of the unique
     * singleton of the playing serie manager
     *
     * @return static PlayingSerieManager&
     */
    static PlayingSerieManager& get();

    /**
     * @brief loads all the level of a given serie file by path
     *
     * @param path the path of the serie file
     *
     * @throw std::invalid_argument if the file cannot be loaded, this
     * exception should be caught in order to display the error controller
     */
    void loadSerieFileContent(const std::string& path);

private:

    /* we use the FIFO (first in first out) method to store the levels names;
       in fact, we add all the levels one by one into the container when we
       load a serie and we pop them one by one in the same order; the queue
       container is directly optimized for that kind of operations */
    std::queue<std::string> levels;
};

}
}

#endif
