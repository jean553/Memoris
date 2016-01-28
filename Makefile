CC = clang++

CFLAGS = -std=c++11 -Weverything -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = bin/main.o bin/MusicFactory.o bin/ScreenFactory.o bin/Context.o bin/Controller.o bin/DirReader.o bin/FileWriter.o bin/StringsListsUtils.o bin/Directories.o bin/Extensions.o bin/Fonts.o bin/Sounds.o bin/Serie.o bin/ButtonWidget.o bin/CursorWidget.o bin/InputTextWidget.o bin/ItemsListWidget.o bin/OrderedItemsListWidget.o bin/TitleBarWidget.o bin/Widget.o bin/MainMenuController.o bin/NewGameController.o bin/EditorMenuController.o bin/EditorLevelController.o bin/EditorSerieController.o bin/OpenSerieController.o

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

bin/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# utils

bin/MusicFactory.o: src/utils/MusicFactory.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/ScreenFactory.o: src/utils/ScreenFactory.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Context.o: src/utils/Context.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Controller.o: src/utils/Controller.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/DirReader.o: src/utils/DirReader.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/FileWriter.o: src/utils/FileWriter.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/StringsListsUtils.o: src/utils/StringsListsUtils.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# defines

bin/Directories.o: src/defines/Directories.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Extensions.o: src/defines/Extensions.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Fonts.o: src/defines/Fonts.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Sounds.o: src/defines/Sounds.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# entities

bin/Serie.o: src/entities/Serie.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# widgets

bin/ButtonWidget.o: src/widgets/ButtonWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/CursorWidget.o: src/widgets/CursorWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/InputTextWidget.o: src/widgets/InputTextWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/ItemsListWidget.o: src/widgets/ItemsListWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/OrderedItemsListWidget.o: src/widgets/OrderedItemsListWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/TitleBarWidget.o: src/widgets/TitleBarWidget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/Widget.o: src/widgets/Widget.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

# controllers

bin/MainMenuController.o: src/main_menu/MainMenuController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/NewGameController.o: src/new_game/NewGameController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/EditorMenuController.o: src/editor_menu/EditorMenuController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/EditorLevelController.o: src/editor_level/EditorLevelController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/EditorSerieController.o: src/editor_serie/EditorSerieController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

bin/OpenSerieController.o: src/open_serie/OpenSerieController.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
