#ifndef _GAME_
#define _GAME_

int isGameOver(int* board , int size , int maxScore);

int insertNumToGame(int* board, int size);

int newGameButton(int* board, int size);

int move(int *board, int size, char direction,int *score, int *highscore);

int moveForDirection(int *board, int size, char direction,int *score,int* highscore) ;

int hasAvailableMoves(int *board, int size);

void menu(int* board, int size,int *maxScore);

void playGame(int* board, int size, int scoreToWin);



#endif
