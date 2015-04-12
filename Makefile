Memoris: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
	g++ -c src/controllers/GameController.cpp -o bin/GameController.o
	g++ -c src/screens/MainMenuController.cpp -o bin/MainMenuController.o
	g++ -c src/screens/Controller.cpp -o bin/Controller.o
	g++ -c src/factories/ScreenFactory.cpp -o bin/ScreenFactory.o
	g++ bin/main.o bin/GameController.o bin/MainMenuController.o bin/Controller.o bin/ScreenFactory.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system
