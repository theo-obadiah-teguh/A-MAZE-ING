FLAGS = -pedantic-errors -std=c++11

array.o: array.cpp transform_array.h
	g++ $(FLAGS) -c array.cpp

shop.o: shop.cpp shop.h transform_array.h
	g++ $(FLAGS) -c shop.cpp

plotting.o: plotting.cpp shop.h transform_array.h players.h
	g++ $(FLAGS) -c $<


main.o: main.cpp transform_array.h shop.h plotting.h players.h
	g++ $(FLAGS) -c $<

main: plotting.o array.o shop.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o plotting.o array.o shop.o

.PHONY: clean
