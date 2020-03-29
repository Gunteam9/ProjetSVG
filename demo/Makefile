# Compilteur
CPPC := g++

#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb
CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Sources & objets

SRC_DEMO_DVD = $(wildcard *.cpp)
SRC_VENDOR = $(wildcard ../vendor/cbor11/*.cpp) $(wildcard ../vendor/exceptions/*.cpp)
SRC_SERVEUR = $(wildcard ../serveur/dataparser.cpp) $(wildcard ../serveur/gtk_drawing.cpp) $(wildcard ../serveur/message.cpp) $(wildcard ../serveur/serveur.cpp) $(wildcard ../serveur/window.cpp)
SRC_CLIENT = $(wildcard ../client/functions.cpp)

OBJ_DEMO_DVD = $(SRC_DEMO_DVD:.cpp=.o)
OBJ_SERVEUR = $(SRC_SERVEUR:.cpp=.o)
OBJ_VENDOR = $(SRC_VENDOR:.cpp=.o)
OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)

# executables
EXEC_DEMO_DVD = ../start_demo_dvd

# Règle de compilation
all : clean $(EXEC_DEMO_DVD)

mem : $(EXEC_DEMO_DVD)
	valgrind --leak-check=full ./$<

$(EXEC_DEMO_DVD) : $(OBJ_VENDOR) $(OBJ_SERVEUR) $(OBJ_CLIENT) $(OBJ_DEMO_DVD)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f *.o start_demo_dvd