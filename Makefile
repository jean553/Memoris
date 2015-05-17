Memoris: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
	g++ -c src/game/GameController.cpp -o bin/GameController.o
	g++ -c src/main_menu/MainMenuController.cpp -o bin/MainMenuController.o
	g++ -c src/new_game/NewGameController.cpp -o bin/NewGameController.o
	g++ -c src/editor_main_menu/EditorMainMenuController.cpp -o bin/EditorMainMenuController.o
	g++ -c src/editor_new_serie/EditorNewSerieController.cpp -o bin/EditorNewSerieController.o
	g++ -c src/utils/Controller.cpp -o bin/Controller.o
	g++ -c src/utils/ScreenFactory.cpp -o bin/ScreenFactory.o
	g++ -c src/utils/MusicFactory.cpp -o bin/MusicFactory.o
	g++ -c src/utils/Context.cpp -o bin/Context.o
	g++ -c src/widgets/InputTextWidget.cpp -o bin/InputTextWidget.o
	g++ bin/main.o bin/GameController.o bin/MainMenuController.o bin/NewGameController.o bin/EditorMainMenuController.o bin/EditorNewSerieController.o bin/Controller.o bin/ScreenFactory.o bin/MusicFactory.o bin/Context.o bin/InputTextWidget.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
