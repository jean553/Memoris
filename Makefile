CC = clang++

CFLAGS = -std=c++11 -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = \
	   build/main.o \
	   build/musics.o \
	   build/window.o \
	   build/controllers.o \
	   build/CellFactory.o \
	   build/Context.o \
	   build/Controller.o \
	   build/DirReader.o \
	   build/FileWriter.o \
	   build/StringsListsUtils.o \
	   build/CellsUtils.o \
	   build/CellsFilter.o \
	   build/Messages.o \
	   build/Directories.o \
	   build/Extensions.o \
	   build/Screens.o \
	   build/Positions.o \
	   build/Serie.o \
	   build/ButtonWidget.o \
	   build/CursorWidget.o \
	   build/InputTextWidget.o \
	   build/ItemsListWidget.o \
	   build/OrderedItemsListWidget.o \
	   build/TitleBarWidget.o \
	   build/CellSelectorWidget.o \
	   build/FrameWidget.o \
	   build/Widget.o \
	   build/MainMenuController.o \
	   build/NewGameController.o \
	   build/EditorMenuController.o \
	   build/EditorLevelController.o \
	   build/EditorSerieController.o \
	   build/OpenSerieController.o \
	   build/OpenLevelController.o \
	   build/GameController.o \
	   build/Level.o \
	   build/Cell.o \
	   build/HasMenuSelectorAnimation.o \
	   build/HiddenCellPicture.o \
	   build/AnimatedBackground.o \
	   build/MenuGradient.o \
	   build/CellsFileRepresentations.o \
	   build/SerieMainMenuController.o \
	   build/OfficialSeriesSelectorController.o \
	   build/SprtTransition.o \
	   build/ErrorController.o \
	   build/FontsManager.o \
	   build/ColorsManager.o \
	   build/SoundsManager.o \
	   build/TexturesManager.o \
	   build/Sound.o \
	   build/NotCopiable.o \
	   build/AbstractMenuController.o \
	   build/MenuItem.o \
	   build/ScrollableListWidget.o

INC = -I includes

$(shell mkdir build)

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# items

build/MenuItem.o: src/MenuItem.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# utils

build/window.o: src/window.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/musics.o: src/musics.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/controllers.o: src/controllers.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FontsManager.o: src/FontsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ColorsManager.o: src/ColorsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/SoundsManager.o: src/SoundsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TexturesManager.o: src/TexturesManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellFactory.o: src/CellFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Context.o: src/Context.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Controller.o: src/Controller.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DirReader.o: src/DirReader.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FileWriter.o: src/FileWriter.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/StringsListsUtils.o: src/StringsListsUtils.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellsUtils.o: src/CellsUtils.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellsFilter.o: src/CellsFilter.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/HiddenCellPicture.o: src/HiddenCellPicture.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/AnimatedBackground.o: src/AnimatedBackground.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/MenuGradient.o: src/MenuGradient.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/SprtTransition.o: src/SprtTransition.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# others

build/NotCopiable.o: src/NotCopiable.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# defines

build/Positions.o: src/Positions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Directories.o: src/Directories.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Extensions.o: src/Extensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Screens.o: src/Screens.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Messages.o: src/Messages.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellsFileRepresentations.o: src/CellsFileRepresentations.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# entities

build/Serie.o: src/Serie.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Level.o: src/Level.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Cell.o: src/Cell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Sound.o: src/Sound.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# widgets

build/ButtonWidget.o: src/ButtonWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CursorWidget.o: src/CursorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/InputTextWidget.o: src/InputTextWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ItemsListWidget.o: src/ItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OrderedItemsListWidget.o: src/OrderedItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TitleBarWidget.o: src/TitleBarWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellSelectorWidget.o: src/CellSelectorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FrameWidget.o: src/FrameWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Widget.o: src/Widget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ScrollableListWidget.o: src/ScrollableListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# controllers

build/MainMenuController.o: src/MainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/NewGameController.o: src/NewGameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorMenuController.o: src/EditorMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorLevelController.o: src/EditorLevelController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorSerieController.o: src/EditorSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OpenSerieController.o: src/OpenSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OpenLevelController.o: src/OpenLevelController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/GameController.o: src/GameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/SerieMainMenuController.o: src/SerieMainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OfficialSeriesSelectorController.o: src/OfficialSeriesSelectorController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/AbstractMenuController.o: src/AbstractMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ErrorController.o: src/ErrorController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# policies

build/HasMenuSelectorAnimation.o: src/HasMenuSelectorAnimation.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
