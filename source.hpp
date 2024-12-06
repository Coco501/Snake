#include <iostream>
#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 39, height = 19;
int x, y, fruitX, fruitY, score;
enum eDirection {stop = 0, left, right, up, down};
eDirection dir;
char topWallChar = '-';
char sideWallChar = '|';
int winScore = 100;

// snake coordinates
int tailX[100];
int tailY[100]; 
int nTail;

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
    for (int i = 0; i < width + 2; i++)
        mvaddch(1, i, topWallChar);
        //std::cout << wallChar << " ";
    //std::cout << std::endl;
}

/// @brief Draw the bottom wall border
void drawBottomWall(){
    for (int i = 0; i < width + 2; i++)
        mvaddch(height + 1, i, topWallChar);
}

/// @brief Draw the interior rows of the screen
void drawInterior(){
    for (int i = 2; i < height + 2; i++){          
        //std::cout << wallChar; 
        mvaddch(i, 0, sideWallChar);

        for (int j = 0; j < width; j++)
            if (y == i && x == j)                // check for snake
                //std::cout << "o";
                mvaddch(i, j, 'o');

            else if (fruitY == i && fruitX == j) // check for fruit
                //std::cout << "•";
                mvprintw(i, j, "•");

            else                                 // print blank
                //std:: cout << " ";              
                mvaddch(i, j, ' ');

        //std::cout << wallChar << std::endl;
        mvaddch(i, width + 1, sideWallChar);
    }
}

/// @brief Check if player has won by checking winScore
bool gameWon(){
    if (score == winScore)
        return true;
    return false;
}

/// @brief Print out the "You won!" screen
void youWon(){
    
}

/// @brief Print out the "You lost..." screen
void youLost(){

}