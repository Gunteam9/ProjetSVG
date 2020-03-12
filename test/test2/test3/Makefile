# Compilteur
CPPC := g++
#options de compilation
CPPFLAGS := --std=c++17 -Wall -Wextra -pedantic -ggdb

CXXFLAGS = $(shell pkg-config --cflags cairo gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs cairo gtk+-3.0 )

# Sources & objets
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
# executable
EXEC = main

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
	rm -f *.o
