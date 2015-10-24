CC = clang++
CFLAGS = -std=c++11 -Weverything -Wno-switch -Wno-switch-enum -Wno-c++98-compat -Werror -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-implicit-fallthrough -ferror-limit=0 
OBJS = bin/main.o bin/MainMenuController.o bin/NewGameController.o bin/EditorSerieController.o bin/OpenSerieController.o bin/Controller.o bin/ScreenFactory.o bin/MusicFactory.o bin/Context.o bin/InputTextWidget.o bin/TitleBarWidget.o bin/ButtonWidget.o bin/CursorWidget.o bin/ItemsListWidget.o bin/OrderedItemsListWidget.o bin/Fonts.o bin/Sounds.o bin/DirReader.o 
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

Memoris: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

bin/main.o: src/main.cpp
	./scripts/style.sh
	./scripts/cppcheck.sh
	$(CC) $(CFLAGS) -c src/main.cpp -o bin/main.o

bin/MainMenuController.o: src/main_menu/MainMenuController.cpp
	$(CC) $(CFLAGS) -c src/main_menu/MainMenuController.cpp -o bin/MainMenuController.o

bin/NewGameController.o: src/new_game/NewGameController.cpp
	$(CC) $(CFLAGS) -c src/new_game/NewGameController.cpp -o bin/NewGameController.o

bin/EditorSerieController.o: src/editor_serie/EditorSerieController.cpp
	$(CC) $(CFLAGS) -c src/editor_serie/EditorSerieController.cpp -o bin/EditorSerieController.o

bin/OpenSerieController.o: src/open_serie/OpenSerieController.cpp
	$(CC) $(CFLAGS) -c src/open_serie/OpenSerieController.cpp -o bin/OpenSerieController.o

bin/Controller.o: src/utils/Controller.cpp
	$(CC) $(CFLAGS) -c src/utils/Controller.cpp -o bin/Controller.o

bin/ScreenFactory.o: src/utils/ScreenFactory.cpp
	$(CC) $(CFLAGS) -c src/utils/ScreenFactory.cpp -o bin/ScreenFactory.o

bin/MusicFactory.o: src/utils/MusicFactory.cpp
	$(CC) $(CFLAGS) -c src/utils/MusicFactory.cpp -o bin/MusicFactory.o

bin/Context.o: src/utils/Context.cpp
	$(CC) $(CFLAGS) -c src/utils/Context.cpp -o bin/Context.o

bin/InputTextWidget.o: src/widgets/InputTextWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/InputTextWidget.cpp -o bin/InputTextWidget.o

bin/TitleBarWidget.o: src/widgets/TitleBarWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/TitleBarWidget.cpp -o bin/TitleBarWidget.o

bin/ButtonWidget.o: src/widgets/ButtonWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/ButtonWidget.cpp -o bin/ButtonWidget.o

bin/CursorWidget.o: src/widgets/CursorWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/CursorWidget.cpp -o bin/CursorWidget.o

bin/ItemsListWidget.o: src/widgets/ItemsListWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/ItemsListWidget.cpp -o bin/ItemsListWidget.o

bin/OrderedItemsListWidget.o: src/widgets/OrderedItemsListWidget.cpp
	$(CC) $(CFLAGS) -c src/widgets/OrderedItemsListWidget.cpp -o bin/OrderedItemsListWidget.o

bin/Fonts.o: src/defines/Fonts.cpp
	$(CC) $(CFLAGS) -c src/defines/Fonts.cpp -o bin/Fonts.o

bin/Sounds.o: src/defines/Sounds.cpp
	$(CC) $(CFLAGS) -c src/defines/Sounds.cpp -o bin/Sounds.o

bin/DirReader.o: src/utils/DirReader.cpp
	$(CC) $(CFLAGS) -c src/utils/DirReader.cpp -o bin/DirReader.o
