CPP  = g++
CXXFLAGS = -g -pedantic -Wno-long-long -O0 -ggdb -Wall -std=c++11

compile: semestralGame.o game.o GameComponent.o Dialogue.o Location.o Item.o Consumable.o Weapon.o Character.o ConsoleGUI.o
	$(CPP) semestralGame.o game.o GameComponent.o Dialogue.o Location.o Item.o Consumable.o Weapon.o Character.o ConsoleGUI.o -o ../"svickpet"

semestralGame.o: semestralGame.cpp
	$(CPP) -c semestralGame.cpp -o semestralGame.o $(CXXFLAGS)

game.o: game.cpp
	$(CPP) -c game.cpp -o game.o $(CXXFLAGS)

GameComponent.o: GameComponent.cpp
	$(CPP) -c GameComponent.cpp -o GameComponent.o $(CXXFLAGS)

Dialogue.o: Dialogue.cpp
	$(CPP) -c Dialogue.cpp -o Dialogue.o $(CXXFLAGS)
	
Location.o: Location.cpp
	$(CPP) -c Location.cpp -o Location.o $(CXXFLAGS)

Item.o: Item.cpp
	$(CPP) -c Item.cpp -o Item.o $(CXXFLAGS)

Consumable.o: Consumable.cpp
	$(CPP) -c Consumable.cpp -o Consumable.o $(CXXFLAGS)

Weapon.o: Weapon.cpp
	$(CPP) -c Weapon.cpp -o Weapon.o $(CXXFLAGS)

Character.o: Character.cpp
	$(CPP) -c Character.cpp -o Character.o $(CXXFLAGS)

ConsoleGUI.o: ConsoleGUI.cpp
	$(CPP) -c ConsoleGUI.cpp -o ConsoleGUI.o $(CXXFLAGS)

