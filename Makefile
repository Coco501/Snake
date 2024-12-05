snake.out: source.cpp
	g++ -g -Wall -Werror source.cpp -o snake.out

clean:
	rm snake.out 
