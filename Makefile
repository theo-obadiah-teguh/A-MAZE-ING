FLAGS = -pedantic-errors -std=c++11

plotting.o: plotting.cpp shop.h players.h
	g++ $(FLAGS) -c $<

players.o: players.cpp players.h plotting.h
	g++ $(FLAGS) -c $<

shop.o: shop.cpp shop.h plotting.h
	g++ $(FLAGS) -c shop.cpp

main.o: main.cpp shop.h plotting.h players.h
	g++ $(FLAGS) -c $<

main: plotting.o players.o shop.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o plotting.o players.o shop.o

.PHONY: clean
