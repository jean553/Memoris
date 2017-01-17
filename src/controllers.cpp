/**
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
 * @file controllers.cpp
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "controllers.hpp"

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
#include "errors.hpp"
#include "PlayingSerieManager.hpp"
#include "EditingLevelManager.hpp"
#include "WinSerieEndingController.hpp"
#include "RemoveGameController.hpp"
#include "PersonalSeriesMenuController.hpp"

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
                getLevelFilePath(
                    serieManager.getSerieType() + "/" +
                        serieManager.getNextLevelName()
                )
            );

            return std::make_unique<GameController>(
                context,
                level
            );
        }
        catch(std::invalid_argument&)
        {
            return getErrorController(
                context,
                errors::CANNOT_OPEN_LEVEL
            );
        }
    }
    /* TODO: #894 to delete, an empty error controller is never called; it
       always contains a message */
    case ControllerId::OpenFileError:
    {
        return getErrorController(
            context,
            errors::CANNOT_OPEN_LEVEL
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
            return getErrorController(
                context,
                errors::CANNOT_OPEN_LEVEL
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
        return getErrorController(
            context,
            errors::UNLOCKED_SERIE
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
        /* by default, if the controller id does not exist, the main
           menu is rendered; it prevents mistakes during screens transitions */
        return std::make_unique<MainMenuController>(context);
    }
    }
}

/**
 *
 */
std::unique_ptr<ErrorController> getErrorController(
    const utils::Context& context,
    const sf::String& message
)
{
    return std::make_unique<ErrorController>(
        context,
        message
    );
}

/**
 *
 */
const std::string getLevelFilePath(const std::string& levelName)
{
    return "data/levels/" + levelName + ".level";
}

}
}
