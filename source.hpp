#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <unistd.h>

bool gameOver;
const int width = 39, height = 19;
int x, y, fruitX, fruitY, score;
enum eDirection {stop = 0, left, right, up, down};
eDirection dir;
char topWallChar = '#';
char sideWallChar = '#';
int winScore = 25;

// snake coordinates
int tailX[100]; // tail x coord
int tailY[100]; // tail y coord
int nTail;      // number of tail segments

/// @brief Print the player's score, centered to the screen
void printScore(){
    int centerX = (width - 7) / 2;
    mvprintw(0, centerX, "Score: %d", score);
    //for (int i = 0; i < (width - 7)/2; i++) // center the "Score: x" according to the width by printing appropriate # of spaces
        ////std::cout << " ";

    //std::cout << "Score: " << score << std::endl;
}

/// @brief Draw the top wall border
void drawTopWall(){
    for (int i = 0; i < (width + 2); i+=2){
        mvaddch(1, i, topWallChar);
        mvaddch(1, i+1, ' ');
    }
}

/// @brief Draw the bottom wall border
void drawBottomWall(){
    for (int i = 0; i < (width + 2); i+=2){
        mvaddch(height + 2, i, topWallChar);
        mvaddch(height + 2, i+1, ' ');
    }
}

/// @brief Draw the interior rows of the screen
void drawInterior(){
    for (int i = 2; i < height + 2; i++){          
        mvaddch(i, 0, sideWallChar);

        for (int j = 1; j < width + 1; j++)
            if (y == i && x == j)                // check for snake
                mvaddch(i, j, 'o');

            else if (fruitY == i && fruitX == j) // check for fruit
                mvprintw(i, j, "x");

            else                                 // print blank
                mvaddch(i, j, ' ');

        mvaddch(i, width + 1, sideWallChar);
    }
}

// /// @brief Check if player has won by checking winScore
// bool gameWon(){
    // if (score == winScore)
        // return true;
    // return false;
// }

/// @brief Print out the "You won!" screen
void youWon(){
    
}

/// @brief Print out the "You lost..." screen
void youLost(){

}