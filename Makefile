CC = clang++

CFLAGS = -std=c++11 -Wall -Werror
DEPS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJS = \
	   build/main.o \
	   build/musics.o \
	   build/window.o \
	   build/controllers.o \
	   build/Context.o \
	   build/Controller.o \
	   build/InputTextWidget.o \
	   build/Widget.o \
	   build/MainMenuController.o \
	   build/NewGameController.o \
	   build/GameController.o \
	   build/Cell.o \
	   build/HiddenCellPicture.o \
	   build/AnimatedBackground.o \
	   build/MenuGradient.o \
	   build/CellsFileRepresentations.o \
	   build/SerieMainMenuController.o \
	   build/OfficialSeriesSelectorController.o \
	   build/ErrorController.o \
	   build/FontsManager.o \
	   build/ColorsManager.o \
	   build/SoundsManager.o \
	   build/TexturesManager.o \
	   build/Sound.o \
	   build/NotCopiable.o \
	   build/AbstractMenuController.o \
	   build/MenuItem.o \
	   build/TimerWidget.o \
	   build/GameDashboard.o

INC = -I includes

$(shell mkdir build)

all: $(OBJS)
	$(CC) $(OBJS) -o bin/Memoris $(DEPS)

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# items

build/MenuItem.o: src/MenuItem.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# utils

build/window.o: src/window.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/musics.o: src/musics.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/controllers.o: src/controllers.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/FontsManager.o: src/FontsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ColorsManager.o: src/ColorsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/SoundsManager.o: src/SoundsManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TexturesManager.o: src/TexturesManager.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Context.o: src/Context.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Controller.o: src/Controller.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/HiddenCellPicture.o: src/HiddenCellPicture.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/AnimatedBackground.o: src/AnimatedBackground.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/MenuGradient.o: src/MenuGradient.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/GameDashboard.o: src/GameDashboard.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# others

build/NotCopiable.o: src/NotCopiable.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# defines

build/CellsFileRepresentations.o: src/CellsFileRepresentations.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# entities

build/Cell.o: src/Cell.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Sound.o: src/Sound.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# widgets

build/InputTextWidget.o: src/InputTextWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/Widget.o: src/Widget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/TimerWidget.o: src/TimerWidget.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

# controllers

build/MainMenuController.o: src/MainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/NewGameController.o: src/NewGameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/GameController.o: src/GameController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/SerieMainMenuController.o: src/SerieMainMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/OfficialSeriesSelectorController.o: src/OfficialSeriesSelectorController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/AbstractMenuController.o: src/AbstractMenuController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

build/ErrorController.o: src/ErrorController.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
