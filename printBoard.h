#ifndef _PRINTBOARD_
#define _PRINTBOARD_

void clearBoard(int* board, int size);

void printBoard(const int *board, int size, int* score , int* highScore);

void printMenu();

void printStartGame(const int maxScore);

#endif
