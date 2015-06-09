Memoris: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
	g++ -c src/game/GameController.cpp -o bin/GameController.o
	g++ -c src/main_menu/MainMenuController.cpp -o bin/MainMenuController.o
	g++ -c src/new_game/NewGameController.cpp -o bin/NewGameController.o
	g++ -c src/editor_serie/EditorSerieController.cpp -o bin/EditorSerieController.o
	g++ -c src/utils/Controller.cpp -o bin/Controller.o
	g++ -c src/utils/ScreenFactory.cpp -o bin/ScreenFactory.o
	g++ -c src/utils/MusicFactory.cpp -o bin/MusicFactory.o
	g++ -c src/utils/Context.cpp -o bin/Context.o
	g++ -c src/widgets/InputTextWidget.cpp -o bin/InputTextWidget.o
	g++ -c src/widgets/TitleBarWidget.cpp -o bin/TitleBarWidget.o
	g++ -c src/widgets/ButtonWidget.cpp -o bin/ButtonWidget.o
	g++ -c src/widgets/CursorWidget.cpp -o bin/CursorWidget.o
	g++ -c src/widgets/ItemsListWidget.cpp -o bin/ItemsListWidget.o
	g++ bin/main.o bin/GameController.o bin/MainMenuController.o bin/NewGameController.o bin/EditorSerieController.o bin/Controller.o bin/ScreenFactory.o bin/MusicFactory.o bin/Context.o bin/InputTextWidget.o bin/TitleBarWidget.o bin/ButtonWidget.o bin/CursorWidget.o bin/ItemsListWidget.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
