/**
 * Memoris
 * Copyright (C) 2017  Jean LELIEVRE
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
 * @file controllers.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "controllers.hpp"

#include "controllers_ids.hpp"
#include "MainMenuController.hpp"
#include "NewGameController.hpp"
#include "SerieMainMenuController.hpp"
#include "OfficialSeriesMenuController.hpp"
#include "GameController.hpp"
#include "EditorMenuController.hpp"
#include "LevelEditorController.hpp"
#include "OpenGameController.hpp"
#include "SerieEditorController.hpp"
#include "Level.hpp"
#include "PlayingSerieManager.hpp"
#include "EditingLevelManager.hpp"
#include "WinSerieEndingController.hpp"
#include "RemoveGameController.hpp"
#include "PersonalSeriesMenuController.hpp"
#include "Context.hpp"
#include "ErrorController.hpp"

#include <SFML/System/String.hpp>

namespace memoris
{
namespace controllers
{

/**
 *
 */
std::unique_ptr<Controller> getControllerById(
    const utils::Context& context,
    const ControllerId& id
)
{
    const sf::String CANNOT_OPEN_LEVEL {"Cannot open level"};

    switch(id)
    {
    case ControllerId::NewGame:
    {
        return std::make_unique<NewGameController>(context);
    }
    case ControllerId::SerieMainMenu:
    {
        return std::make_unique<SerieMainMenuController>(context);
    }
    case ControllerId::OfficialSeriesMenu:
    {
        return std::make_unique<OfficialSeriesMenuController>(context);
    }
    case ControllerId::Game:
    {
        try
        {
            const auto& editedLevel =
                context.getEditingLevelManager().getLevel();

            auto& serieManager = context.getPlayingSerieManager();

            if (editedLevel != nullptr)
            {
                serieManager.reinitialize();

                return std::make_unique<GameController>(
                    context,
                    editedLevel,
                    false
                );
            }

            std::string levelPath = "data/levels/" +
                serieManager.getSerieType() + "/" +
                serieManager.getNextLevelName() + ".level";

            /* creates a level object using the next level file path; this path
               is located inside the context object; this part of the code
               throws an exception if an error occures during the file reading
               process; we use auto, the generates type is
               std::shared_ptr<entities::Level>; create this pointer here
               instead of directly creating it inside the game controller makes
               the code easier to maintain; the level pointer is used in the
               game controller and also in the LevelAnimation object; */
            auto level = std::make_shared<entities::Level>(
                context,
                levelPath
            );

            return std::make_unique<GameController>(
                context,
                level
            );
        }
        catch(std::invalid_argument&)
        {
            return std::make_unique<ErrorController>(
                context,
                CANNOT_OPEN_LEVEL
            );
        }
    }
    case ControllerId::OpenFileError:
    {
        return std::make_unique<ErrorController>(
            context,
            CANNOT_OPEN_LEVEL
        );
    }
    case ControllerId::EditorMenu:
    {
        return std::make_unique<EditorMenuController>(context);
    }
    case ControllerId::LevelEditor:
    {
        const auto& editedLevel = context.getEditingLevelManager().getLevel();

        if (editedLevel != nullptr)
        {
            const auto& playingTime =
                context.getPlayingSerieManager().getPlayingTime();

            const auto& levelManager = context.getEditingLevelManager();

            editedLevel->setCellsFromCharactersList(
                levelManager.getCellsBackup()
            );

            return std::make_unique<LevelEditorController>(
                context,
                editedLevel,
                static_cast<bool>(playingTime)
            );
        }

        try
        {
            auto level = std::make_shared<entities::Level>(context);

            return std::make_unique<LevelEditorController>(
                context,
                level
            );
        }
        catch(std::invalid_argument&)
        {
            return std::make_unique<ErrorController>(
                context,
                CANNOT_OPEN_LEVEL
            );
        }
    }
    case ControllerId::OpenGame:
    {
        return std::make_unique<OpenGameController>(context);
    }
    case ControllerId::SerieEditor:
    {
        return std::make_unique<SerieEditorController>(context);
    }
    case ControllerId::UnlockedSerieError:
    {
        return std::make_unique<ErrorController>(
            context,
            "This serie is locked."
        );
    }
    case ControllerId::WinSerie:
    {
        return std::make_unique<WinSerieEndingController>(context);
    }
    case ControllerId::RemoveGame:
    {
        return std::make_unique<RemoveGameController>(context);
    }
    case ControllerId::PersonalSeriesMenu:
    {
        return std::make_unique<PersonalSeriesMenuController>(context);
    }
    default:
    {
        return std::make_unique<MainMenuController>(context);
    }
    }
}

}
}
