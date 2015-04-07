Memoris: src/main.cpp
	g++ -c src/main.cpp -o bin/main.o
	g++ -c src/controllers/GameController.cpp -o bin/GameController.o
	g++ bin/main.o bin/GameController.o -o bin/Memoris -lsfml-graphics -lsfml-window -lsfml-system
