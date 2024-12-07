#include "source.hpp"

void setup(){
    srand(time(0));     // set random seed for rand()
    gameOver = false;   // set game state to running
    score = 0;          // initialize score to be 0
    dir = stop;         // snake stopped before any input
    x = 1 + width/2;    // start our snake in the middle of the window
    y = 2 + height/2;   // + 1 accounts for Score at the top
    fruitX = 1 + rand() % width;  // + 1 to account for side wall
    fruitY = 2 + rand() % height; // + 2 to account for top wall and score line  
    while ((fruitX == x) && (fruitY = y)){ // make sure fruit does not start in same spot as snake
        fruitX = 1 + rand() % width; 
        fruitY = 2 + rand() % height; 
    }
}

void draw(){
    erase();
    printScore();
    drawTopWall();
    drawInterior();
    drawBottomWall();
    refresh(); // refresh the screen to show new updates
}

void input(){
    int key = getch(); // get user input

    switch (key){
        case 'w':
        case 'W':
            dir = up;
            break;
        case 'a':
        case 'A':
            dir = left;
            break;
        case 's':
        case 'S':
            dir = down;
            break;
        case 'd':
        case 'D':
            dir = right;
            break;
        case 27: // escape key 
            gameOver = true; // eventually turn into gamePaused, so we can pause and resume;
            break;
        default:        // keep current direction
            break;
        
    }
}

void logic(){
    switch (dir){
        case up:
            y--;
            break;
        case left:
            x--;
            break;
        case down:
            y++;
            break;
        case right:
            x++;
            break;
        case stop: 
            break;
    }

    if (x <= 0 || x >= width + 1 || y <= 1 || y >= height + 2){ // check for wall collision
        gameOver = true; // hit a wall
        return; 
    }

    if (x == fruitX && y == fruitY){ // check for fruit eating
        score++;
        fruitX = 1 + rand() % width;
        fruitY = 2 + rand() % height;
        while ((fruitX == x) && (fruitY = y)){
            fruitX = 1 + rand() % width; 
            fruitY = 2 + rand() % height; 
        }
    }
}

int main(){
    initscr();      // initialize screen
    noecho();       // do not echo input strokes 
    cbreak();       // disable line buffering
    curs_set(0);    // disable cursor in window
    nodelay(stdscr, TRUE); // make getch() non-blocking

    setup();

    while(!gameOver){
        draw();
        input();
        logic();
        if (score == winScore)
            gameOver = true;
        usleep(150000);
    }

    if (score == winScore)
        youWon();
    else
        youLost();
    
    endwin(); // end window
    return 0;
}