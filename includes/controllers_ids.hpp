/*
 * Memoris
 * Copyright (C) 2016  Jean LELIEVRE
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
 * @brief enumeration with all the controllers
 */

namespace memoris
{
namespace controllers
{

enum class ControllerId
{
    NoController,
    MainMenu,
    NewGame,
    Game,
    SerieMainMenu,
    OfficialSeriesMenu,
    EditorMenu,
    LevelEditor,
    OpenGame,
    SerieEditor,
    WinSerie,
    RemoveGame,
    PersonalSeriesMenu,

    /* TODO: #894 delete this id when each error
       controller has his own message */
    OpenFileError,
    UnlockedSerieError
};

}
}
