# Compilteur
CPPC := g++

#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb
CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Sources & objets
SRC_VENDOR = $(wildcard vendor/cbor11/*.cpp) $(wildcard vendor/exceptions/*.cpp)
SRC_CLIENT = $(wildcard client/*.cpp)
SRC_SERVEUR = $(wildcard serveur/*.cpp)
SRC_DEMO_DVD = $(wildcard serveur/dataparser.cpp) $(wildcard serveur/gtk_drawing.cpp) $(wildcard serveur/message.cpp) $(wildcard serveur/serveur.cpp) $(wildcard serveur/window.cpp) $(wildcard client/functions.cpp) $(wildcard demo/*.cpp)

OBJ_VENDOR = $(SRC_VENDOR:.cpp=.o)
OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)
OBJ_SERVEUR = $(SRC_SERVEUR:.cpp=.o)
OBJ_DEMO_DVD = $(SRC_DEMO_DVD:.cpp=.o)

# executables
EXEC_CLIENT = start_client
EXEC_SERVEUR = start_serveur
EXEC_DEMO_DVD = start_demo_dvd

# Règle de compilation
all : clean $(EXEC_CLIENT) $(EXEC_SERVEUR) $(EXEC_DEMO_DVD)

mem : $(EXEC_CLIENT)
	valgrind --leak-check=full ./$<

$(EXEC_DEMO_DVD) : $(OBJ_DEMO_DVD) $(OBJ_VENDOR)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC_CLIENT) : $(OBJ_VENDOR) $(OBJ_CLIENT)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC_SERVEUR) : $(OBJ_VENDOR) $(OBJ_SERVEUR)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f serveur/*.o client/*.o vendor/exceptions/*.o start_client start_serveur start_demo_dvd