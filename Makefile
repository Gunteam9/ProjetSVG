# Compilteur
CPPC := g++

#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb
CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Sources & objets
SRC_VENDOR = $(wildcard vendor/cbor11/*.cpp) $(wildcard vendor/exceptions/*.cpp)
SRC_CLIENT = $(wildcard client/*.cpp) $(wildcard client/test_gtk/*.cpp) 
SRC_CLIENT_GRAPHIQUE = $(wildcard client/test_gtk/*.cpp) 
SRC_SERVEUR = $(wildcard serveur/*.cpp)

OBJ_VENDOR = $(SRC_VENDOR:.cpp=.o)
OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)
OBJ_CLIENT_GRAPHIQUE = $(SRC_CLIENT_GRAPHIQUE:.cpp=.o)
OBJ_SERVEUR = $(SRC_SERVEUR:.cpp=.o)

# executables
EXEC_CLIENT = start_client
EXEC_CLIENT_GRAPHIQUE = start_client_graphique
EXEC_SERVEUR = start_serveur

# Règle de compilation
all : clean $(EXEC_CLIENT) $(EXEC_SERVEUR) $(EXEC_CLIENT_GRAPHIQUE)

mem : $(EXEC_CLIENT)
	valgrind --leak-check=full ./$<

$(EXEC_CLIENT) : $(OBJ_VENDOR) $(OBJ_CLIENT)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC_CLIENT_GRAPHIQUE) : $(OBJ_VENDOR) $(OBJ_CLIENT) $(OBJ_CLIENT_GRAPHIQUE)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(EXEC_SERVEUR) : $(OBJ_VENDOR) $(OBJ_SERVEUR)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f serveur/*.o client/*.o vendor/exceptions/*.o client/test_gtk/*.o start_client start_serveur