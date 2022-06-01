CXX = g++
CXXFLAGS = -std=c++11
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJECTS = main.o Menu.o InputVal.o Game.o Person.o Space.o Foyer.o Puzzle_Room.o Library.o Treasure_Room.o Alchemist_Room.o Atrium.o

SOURCES = main.cpp Menu.cpp InputVal.cpp Game.cpp Person.cpp Space.cpp Foyer.cpp Puzzle_Room.cpp Library.cpp Treasure_Room.cpp Alchemist_Room.cpp Atrium.cpp

HEADERS = Menu.hpp InputVal.hpp Game.hpp Person.hpp Space.hpp Foyer.hpp Puzzle_Room.hpp Library.hpp Treasure_Room.hpp Alchemist_Room.hpp Atrium.hpp

project1: $(OBJECTS) $(HEADERS)
		$(CXX) $(CXXFLAGS) $(OBJECTS) -o final

$(OBJECTS): $(SOURCES)

clean:
	rm *.o final
	