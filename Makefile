Memoris: src/main.cpp
	./scripts/style.sh
	./scripts/cppcheck.sh
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/main.cpp -o bin/main.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/game/GameController.cpp -o bin/GameController.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/main_menu/MainMenuController.cpp -o bin/MainMenuController.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/new_game/NewGameController.cpp -o bin/NewGameController.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/editor_serie/EditorSerieController.cpp -o bin/EditorSerieController.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/utils/Controller.cpp -o bin/Controller.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/utils/ScreenFactory.cpp -o bin/ScreenFactory.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/utils/MusicFactory.cpp -o bin/MusicFactory.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/utils/Context.cpp -o bin/Context.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/widgets/InputTextWidget.cpp -o bin/InputTextWidget.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/widgets/TitleBarWidget.cpp -o bin/TitleBarWidget.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/widgets/ButtonWidget.cpp -o bin/ButtonWidget.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/widgets/CursorWidget.cpp -o bin/CursorWidget.o
	clang++ -Weverything -Wno-switch -Wno-switch-enum -Werror -Wno-padded -ferror-limit=0 -c src/widgets/ItemsListWidget.cpp -o bin/ItemsListWidget.o
	clang++ bin/main.o bin/GameController.o bin/MainMenuController.o bin/NewGameController.o bin/EditorSerieController.o bin/Controller.o bin/ScreenFactory.o bin/MusicFactory.o bin/Context.o bin/InputTextWidget.o bin/TitleBarWidget.o bin/ButtonWidget.o bin/CursorWidget.o bin/ItemsListWidget.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
