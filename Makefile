FLAGS = -pedantic-errors -std=c++11

plotting.o = plotting.cpp players.h
	g++ $(FLAGS) -c $<

main.o: main.cpp plotting.h players.h
	g++ $(FLAGS) -c $<

main: plotting.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o plotting.o

.PHONY: clean