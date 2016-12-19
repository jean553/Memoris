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
 * @file DoubleSelectionListWidget.hpp
 * @package widgets
 * @author Jean LELIEVRE <Jean.LELIEVRE@supinfo.com>
 */

#include "DoubleSelectionListWidget.hpp"

#include "SelectionListWidget.hpp"
#include "DirectoryReader.hpp"

namespace memoris
{
namespace widgets
{

class DoubleSelectionListWidget::Impl
{

public:

    Impl(const utils::Context& context) :
        allLevelsList(
            context,
            100.f
        ),
        serieLevelsList(
            context,
            890.f
        )
    {
        /* this class is generic for any kind of double selection list,
           for organization purposes, we just load the lists content here */
        allLevelsList.setList(
            context,
            utils::getFilesFromDirectory("data/levels/personals")
        );
    }

    widgets::SelectionListWidget allLevelsList;
    widgets::SelectionListWidget serieLevelsList;
};

/**
 *
 */
DoubleSelectionListWidget::DoubleSelectionListWidget(
    const utils::Context& context
) :
    impl(std::make_unique<Impl>(context))
{
}

/**
 *
 */
DoubleSelectionListWidget::~DoubleSelectionListWidget() noexcept = default;

/**
 *
 */
void DoubleSelectionListWidget::display(const utils::Context& context)
    const &
{
    impl->allLevelsList.display(context);
    impl->serieLevelsList.display(context);
}

/**
 *
 */
const widgets::SelectionListWidget& DoubleSelectionListWidget::getLevelsList()
    const & noexcept
{
    return impl->allLevelsList;
}

}
}
