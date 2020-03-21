# Compilteur
CPPC := g++

#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb
CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Sources & objets
SRC_CLIENT = $(wildcard *.cpp)

OBJ_CLIENT = $(SRC_CLIENT:.cpp=.o)

# executables
EXEC_CLIENT = start_client

# Règle de compilation
all : clean $(EXEC_CLIENT)

mem : $(EXEC_CLIENT)
	valgrind --leak-check=full ./$<

$(EXEC_CLIENT) : $(OBJ_CLIENT)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f *.o start_client 