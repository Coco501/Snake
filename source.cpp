#include "source.hpp"

void setup(){
    srand(time(0));     // set random seed for rand()
    gameOver = false;   // set game state to running
    score = 0;          // initialize score to be 0
    dir = stop;         // snake stopped before any input
    x = width/2;        // start our snake in the middle of the window
    y = height/2 + 1;   // + 1 accounts for Score at the top
    fruitX = rand() % width; //start fruit in random spot
    fruitY = rand() % height;
    while ((fruitX == x) && (fruitY = y)){ // make sure fruit does not start in same spot as snake
        fruitX = rand() % width; 
        fruitY = rand() % height;
    }
}

void draw(){
    clear();
    drawTopWall();
    drawInterior();
    drawBottomWall();
    printScore();
    refresh(); // refresh the screen to show new updates
}

void input(){
    char input;
    std::cin >> input;
}

void logic(){
    
}

int main(){
    initscr();
    noecho();
    curs_set(0);

    setup();

    while(!gameOver){
        draw();
        input();
        logic();
        if (gameWon())
            gameOver = true;
    }

    if (gameWon())
        youWon();
    else
        youLost();
    
    endwin(); // end window
    return 0;
}