MAINPROG=timeDilation

SOURCES:=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
FLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Weffc++ -fsanitize=address,leak -fuse-ld=gold

all: $(SOURCES) $(MAINPROG)

$(MAINPROG): $(OBJECTS)
	g++ $(FLAGS) $(OBJECTS) -o $@

.cpp.o:
	g++ $(FLAGS) -c $< -o $@

clean:
	rm *.o $(MAINPROG)

runCpp: $(MAINPROG)
	./$(MAINPROG)

runPython:
	./timeDilationRevised.py

