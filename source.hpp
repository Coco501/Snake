#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

bool gameOver;
// regular terminal cell width
//const int width = 39, height = 19;

// square terminal cell width 
const int width = 19, height = 19;

int x, y, fruitX, fruitY, score;
enum eDirection {stop = 0, left, right, up, down};
eDirection dir;
char topWallChar = '#';
char sideWallChar = '#';
int winScore = 10;

// snake coordinates
int tailX[100]; // tail x coord
int tailY[100]; // tail y coord
int nTail;      // number of tail segments

/// @brief Print the player's score, centered to the screen
void printScore(){
    int centerX = (width - 7) / 2;
    mvprintw(0, centerX, "Score: %d", score);
}

/// @brief Draw the top wall border
void drawTopWall(){
    // regular terminal cell width
    //for (int i = 0; i < (width + 2); i+=2){
        //mvaddch(1, i, topWallChar);
        //mvaddch(1, i+1, ' ');
    //}

    // square terminal cell width
    for (int i = 0; i < (width + 2); i++){
        mvaddch(1, i, topWallChar);
    }
}

/// @brief Draw the bottom wall border
void drawBottomWall(){
    // regular terminal cell width
    //for (int i = 0; i < (width + 2); i+=2){
        //mvaddch(height + 2, i, topWallChar);
        //mvaddch(height + 2, i+1, ' ');
    //}

    // square terminal cell width
    for (int i = 0; i < (width + 2); i++){
        mvaddch(height + 2, i, topWallChar);
    }
}

/// @brief Draw the interior rows of the screen
void drawInterior(){
    for (int i = 2; i < height + 2; i++){          
        mvaddch(i, 0, sideWallChar);

        for (int j = 1; j < width + 1; j++)
            if (y == i && x == j)   // check for snake head
                mvaddch(i, j, 'o');
            
            else if (fruitY == i && fruitX == j)    // check for fruit
                mvaddch(i, j, 'x');

            else{
                bool isTail = false;
                for (int k = 0; k < nTail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        mvaddch(i, j, 'o');
                        isTail = true;
                        break;
                    }
                }
                if (isTail == false)    // print blank
                    mvaddch(i, j, ' ');
            }

        mvaddch(i, width + 1, sideWallChar);
    }
}

/// @brief Print out the "You won!" screen
void youWon(){
    mvprintw((height + 2)/2 + 1, (width+2)/2 - 4, "You won!"); 
    refresh();
    usleep(10000000);
}

/// @brief Print out the "You lost..." screen
void youLost(){
    mvprintw((height + 2)/2 + 1, (width+2)/2 - 5, "You lost..."); 
    refresh();
    usleep(10000000);
}
