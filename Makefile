snake.out: source.cpp
	g++ -g -Wall -Werror source.cpp -o snake.out -lncurses

clean:
	rm snake.out 
