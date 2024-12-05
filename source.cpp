#include <iostream>
#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 10, height = 10;
int x, y, fruitX, fruitY, score;
enum Direction {stop = 0, left, right, up, down};
Direction dir;

void setup(){
    srand(time(0));     // set random seed for rand()
    gameOver = false;   // set game state to running
    score = 0;          // initialize score to be 0
    dir = stop;         // snake stopped before any input
    x = width/2;        // start our snake in the middle of the window
    y = height/2;
    fruitX = rand() % width; //start fruit in random spot
    fruitY = rand() % height;
}

void draw(){
   // system("clear");                          // clear screen
    char wallChar = '#';

    for (int i = 0; i < (width + 2); i++)         // draw top wall of #
        std::cout << wallChar;
    std::cout << std::endl;

    for (int i = 0; i < height; i++){   // draw all interior rows
        std::cout << wallChar;
        for (int j = 0; j < width; j++)
            std:: cout << " ";
        std::cout << wallChar << std::endl;
    }

    for (int i = 0; i < (width + 2); i++)         // draw bottom wall of #
        std::cout << wallChar;
    std::cout << std::endl; 
}

void input(){
    char input;
    std::cin >> input;
}

void logic(){

}

int main(){
    setup();

    while(!gameOver){
        draw();
        input();
        logic();
    }

    return 0;
}