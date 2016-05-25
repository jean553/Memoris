CC = clang++

CFLAGS = -std=c++11 -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = \
	   build/main.o \
	   build/MusicFactory.o \
	   build/ControllerFactory.o \
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
	   build/Fonts.o \
	   build/Sounds.o \
	   build/Colors.o \
	   build/Screens.o \
	   build/Window.o \
	   build/Dimensions.o \
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
	   build/SerieMainMenuController.o

INC = -I includes

$(shell mkdir build)

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# utils

build/MusicFactory.o: src/MusicFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ControllerFactory.o: src/ControllerFactory.cpp
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

# defines

build/Colors.o: src/Colors.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Window.o: src/Window.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Dimensions.o: src/Dimensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Positions.o: src/Positions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Directories.o: src/Directories.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Extensions.o: src/Extensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Fonts.o: src/Fonts.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Sounds.o: src/Sounds.cpp
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

# policies

build/HasMenuSelectorAnimation.o: src/HasMenuSelectorAnimation.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
