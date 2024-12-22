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
    if (inputProcessed)
        return;

    int key = getch(); // get user input

    switch (key){
        case 'w':
        case 'W':
            if (nTail == 0 || (nTail >= 1 && dir != down)){
                dir = up;
                inputProcessed = true;
            }
            break;
        case 'a':
        case 'A':
            if (nTail == 0 || (nTail >= 1 && dir != right)){
                dir = left;
                inputProcessed = true;
            }
            break;
        case 's':
        case 'S':
            if (nTail == 0 || (nTail >= 1 && dir != up)){
                dir = down;
                inputProcessed = true;
            }
            break;
        case 'd':
        case 'D':
            if (nTail == 0 || (nTail >= 1 && dir != left)){
                dir = right;
                inputProcessed = true;
            }
            break;
        case 27: // escape key 
            gameOver = true; // eventually turn into gamePaused, so we can pause and resume;
            break;
        default:        // keep current direction
            break;
    }
}

void logic(){
    // previous head positions
    int prevX = x, prevY = y;
    int prev2X, prev2Y;

    // move head
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

    // check for wall collision
    if (x <= 0 || x >= width + 1 || y <= 1 || y >= height + 2){
        gameOver = true; // hit a wall
        return; 
    }

    // check for tail collision
    for (int i = 0; i < nTail; i++){
        if (tailX[i] == x && tailY[i] == y){
            gameOver = true;
            return;
        }
    }

    // move tail
    for (int i = 0; i < nTail; i++){
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // check for fruit eating
    if (x == fruitX && y == fruitY){ 
        score++;   // increment score
        nTail++;   // increase tail length
        // new fruit position
        fruitX = 1 + rand() % width;
        fruitY = 2 + rand() % height;
        // ensure fruit does not spawn on snake
        while (true){
            bool onSnake = false;
            if (fruitX == x && fruitY == y)
                onSnake = true;
            else {
                for (int i = 0; i < nTail; i++){
                    if (fruitX == tailX[i] && fruitY == tailY[i]){
                        onSnake = true;
                        break;
                    }
                }
            }
            if (onSnake == false)
                break;

            else{
                fruitX = 1 + rand() % width;
                fruitY = 2 + rand() % height;
            }
        }



        while ((fruitX == x) && (fruitY = y)){
            fruitX = 1 + rand() % width; 
            fruitY = 2 + rand() % height; 
        }
    }
    inputProcessed = false; 
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
        draw();
        usleep(125000);
    }

    if (score == winScore)
        youWon();
    else
        youLost();
    
    endwin(); // end window
    return 0;
}