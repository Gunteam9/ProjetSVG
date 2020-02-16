# Compilteur
CPPC := g++
#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb 
# Sources & objets
SRC= $(wildcard client.cpp) $(wildcard ../cbor11/*.cpp) $(wildcard ../exceptions/*.cpp)
OBJ= $(SRC:.cpp=.o)

# executable
EXEC = client

CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Règle de compilation
all : clean $(EXEC)

mem : $(EXEC)
	valgrind --leak-check=full ./$<

$(EXEC) : $(OBJ)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f *.o client