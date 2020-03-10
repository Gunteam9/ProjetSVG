# Compilteur
CPPC := g++
#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb -I/home/samir/Projets/C++/corbeau_neonakis_toularhmine_trimoulet/vendor/color/src
# Sources & objets
SRC= $(wildcard *.cpp) $(wildcard ../vendor/cbor11/*.cpp) $(wildcard ../vendor/exceptions/*.cpp)
OBJ= $(SRC:.cpp=.o)

# executable
EXEC = ../start_serveur

CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0 librsvg-2.0 tinyxml2)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 librsvg-2.0 tinyxml2)

# Règle de compilation
all : clean $(EXEC)

mem : $(EXEC)
	valgrind --leak-check=full ./$<

$(EXEC) : $(OBJ)
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h %.hpp
	$(CPPC) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY : clean

clean:
	rm -f *.o ../start_serveur