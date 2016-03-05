CC = clang++

CFLAGS = -std=c++11 -Weverything -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = build/main.o build/MusicFactory.o build/ControllerFactory.o build/Context.o build/Controller.o build/DirReader.o build/FileWriter.o build/StringsListsUtils.o build/Directories.o build/Extensions.o build/Fonts.o build/Sounds.o build/Colors.o build/Window.o build/Dimensions.o build/Positions.o build/Serie.o build/ButtonWidget.o build/CursorWidget.o build/InputTextWidget.o build/ItemsListWidget.o build/OrderedItemsListWidget.o build/TitleBarWidget.o build/CellSelectorWidget.o build/Widget.o build/MainMenuController.o build/NewGameController.o build/EditorMenuController.o build/EditorLevelController.o build/EditorSerieController.o build/OpenSerieController.o build/Level.o build/Cell.o build/EmptyCell.o build/DepartureCell.o build/ArrivalCell.o build/StarCell.o build/LifeCell.o build/HasMenuSelectorAnimation.o

INC = -I includes

$(shell mkdir build)

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# utils

build/MusicFactory.o: src/utils/MusicFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ControllerFactory.o: src/utils/ControllerFactory.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Context.o: src/utils/Context.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Controller.o: src/utils/Controller.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DirReader.o: src/utils/DirReader.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FileWriter.o: src/utils/FileWriter.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/StringsListsUtils.o: src/utils/StringsListsUtils.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# defines

build/Colors.o: src/defines/Colors.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Window.o: src/defines/Window.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Dimensions.o: src/defines/Dimensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Positions.o: src/defines/Positions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Directories.o: src/defines/Directories.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Extensions.o: src/defines/Extensions.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Fonts.o: src/defines/Fonts.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Sounds.o: src/defines/Sounds.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# entities

build/Serie.o: src/entities/Serie.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Level.o: src/entities/Level.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Cell.o: src/entities/Cell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EmptyCell.o: src/entities/EmptyCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/DepartureCell.o: src/entities/DepartureCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ArrivalCell.o: src/entities/ArrivalCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/StarCell.o: src/entities/StarCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/LifeCell.o: src/entities/LifeCell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# widgets

build/ButtonWidget.o: src/widgets/ButtonWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CursorWidget.o: src/widgets/CursorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/InputTextWidget.o: src/widgets/InputTextWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ItemsListWidget.o: src/widgets/ItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OrderedItemsListWidget.o: src/widgets/OrderedItemsListWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TitleBarWidget.o: src/widgets/TitleBarWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/CellSelectorWidget.o: src/widgets/CellSelectorWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Widget.o: src/widgets/Widget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# controllers

build/MainMenuController.o: src/main_menu/MainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/NewGameController.o: src/new_game/NewGameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorMenuController.o: src/editor_menu/EditorMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorLevelController.o: src/editor_level/EditorLevelController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/EditorSerieController.o: src/editor_serie/EditorSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OpenSerieController.o: src/open_serie/OpenSerieController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# policies

build/HasMenuSelectorAnimation.o: src/policies/HasMenuSelectorAnimation.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
