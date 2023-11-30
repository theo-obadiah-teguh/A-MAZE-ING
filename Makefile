FLAGS = -pedantic-errors -std=c++11

plotting.o: plotting.cpp shop.h players.h
	g++ $(FLAGS) -c $<

players.o: players.cpp players.h plotting.h
	g++ $(FLAGS) -c $<
	
#add monster.h to shop.o
shop.o: shop.cpp shop.h plotting.h monster.h
	g++ $(FLAGS) -c shop.cpp

#try compile monster
monster.o: monster.cpp players.h
	g++ $(FLAGS) -c $<

#add monster.h to main.o
main.o: main.cpp shop.h plotting.h players.h monster.h aesthetics.h
	g++ $(FLAGS) -c $<

#add monster.o
main: plotting.o players.o shop.o monster.o main.o 
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o plotting.o players.o shop.o monster.o

.PHONY: clean
