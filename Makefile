snake.out: source.cpp
	g++ -g -Wall -Werror source.cpp source.hpp -o snake.out -lncurses

clean:
	rm snake.out 
