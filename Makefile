Memoris: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
	g++ -c src/controllers/GameController.cpp -o bin/GameController.o
	g++ -c src/screens/MainMenuScreen.cpp -o bin/MainMenuScreen.o
	g++ -c src/screens/Screen.cpp -o bin/Screen.o
	g++ -c src/factories/ScreenFactory.cpp -o bin/ScreenFactory.o
	g++ bin/main.o bin/GameController.o bin/MainMenuScreen.o bin/Screen.o bin/ScreenFactory.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system
