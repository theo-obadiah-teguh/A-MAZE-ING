FLAGS = -pedantic-errors -std=c++11

shop.o: shop.cpp shop.h plotting.h
	g++ $(FLAGS) -c shop.cpp

plotting.o: plotting.cpp shop.h players.h
	g++ $(FLAGS) -c $<

main.o: main.cpp shop.h plotting.h players.h
	g++ $(FLAGS) -c $<

main: plotting.o shop.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o plotting.o shop.o

.PHONY: clean
