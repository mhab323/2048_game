#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "game.h"
#include "printBoard.h"



int isGameOver(int* board , int size , int maxScore)
{
	for (int i = 0; i < size*size; i++)
	{
		if (*(board + i) == maxScore)
		{
			return 1;
		}
	}
	return 0;

}


int insertNumToGame(int* board, int size)
{
	int randomRow , randomCol, numberToAdd;
	int added = 0;
	for (int i = 0; i < size; i++)
    	{
        	for (int j = 0; j < size; j++)
        	{
	    		if (*(board + i*size + j) == 0)
	    		{
        			do
        			{
                    			randomRow = rand()%(size);
                    			randomCol = rand()%(size);
        
                    			double r;
        
                    			r = (double)rand()/RAND_MAX;
                    			if (r <= 0.7)
                    			{
                        			numberToAdd = 2;
                    			}
                    			else
                    			{
                        			numberToAdd = 4;
                    			}
                
                    			if (*(board+size*randomRow+randomCol) == 0)
                    			{
                        			*(board+size*randomRow+randomCol) = numberToAdd;
                        			added = 1;
                    			}
                		} while (!added);
        			return 1;
            		}
        	}
    	}
    	return 0;
}





int newGameButton(int* board, int size)
{
	clearBoard(board , size);
    	int openCell;
    	for(int i = 0; i < 2; i++)
    	{
        	openCell = insertNumToGame(board,size);
    	}
    	if (openCell == 0)
    	{
        	printf("No More Places\n");
    	}
    	return 1;
}




int move(int *board, int size, char direction,int *score, int *highscore)
{
	int boardChanged = 0;
	boardChanged = moveForDirection(board, size, direction, score, highscore);
    	if (boardChanged)
    	{	
        	insertNumToGame(board, size);
    	}
    
    	return boardChanged;
}




int moveForDirection(int *board, int size, char direction, int *score, int *highscore)
{
	int isVertical = (direction == 'u' || direction == 'd'); 
	int reverse = (direction == 'd' || direction == 'r');   
	int step = reverse ? -1 : 1;
	int boardChanged = 0;

	for (int i = 0; i < size; i++) 
	{
		int nextID = reverse ? size - 1 : 0;

        
	        for (int j = reverse ? size - 1 : 0; reverse ? j >= 0 : j < size; j += step) 
	        {
			int index = isVertical ? j * size + i : i * size + j;
			if (*(board + index) != 0) 
			{
                		int targetIndex = isVertical ? nextID * size + i : i * size + nextID;
                		if (*(board + targetIndex) == 0)
                		{
                    			*(board + targetIndex) = *(board + index);
                    			*(board + index) = 0;
                    			boardChanged = 1;
                		}
                		else if (nextID != j)
                		{
                    			*(board + targetIndex) = *(board + index);
                    			*(board + index) = 0;
                    			boardChanged = 1;
                		}
                		nextID += step;
            		}
		}

        
        	for (int j = reverse ? size - 1 : 0; reverse ? j > 0 : j < size - 1; j += step) 
        	{
            		int index = isVertical ? j * size + i : i * size + j;
            		int neighborIndex = index + (isVertical ? (reverse ? -size : size) : (reverse ? -1 : 1));
            		if (*(board + index) != 0 && *(board + index) == *(board + neighborIndex)) 
            		{
                		*(board + index) *= 2;
                		*score += *(board + index);  
                		*highscore = (*score > *highscore) ? *score : *highscore;  
                		*(board + neighborIndex) = 0;
                		boardChanged = 1;
            		    	break; 
            		}
        	}

       
        	nextID = reverse ? size - 1 : 0;
        	for (int j = reverse ? size - 1 : 0; reverse ? j >= 0 : j < size; j += step) 
        	{
            		int index = isVertical ? j * size + i : i * size + j;
            		if (*(board + index) != 0) 
            		{
                		int targetIndex = isVertical ? nextID * size + i : i * size + nextID;
                		if (*(board + targetIndex) == 0)
                		{
                    			*(board + targetIndex) = *(board + index);
                    			*(board + index) = 0;
                    			boardChanged = 1;
                		}
                		nextID += step;
            		}
        	}
	}
    	return boardChanged;
}






int hasAvailableMoves(int *board, int size)
{
	for (int i = 0; i < size; i++)
    	{
        	for (int j = 0; j < size; j++)
        	{
			int current = *(board + i * size + j);
            		if (current == 0) return 1;
            		if (i > 0 && current == *(board + (i - 1) * size + j)) return 1;
            		if (i < size - 1 && current == *(board + (i + 1) * size + j)) return 1;
            		if (j > 0 && current == *(board + i * size + (j - 1))) return 1;
            		if (j < size - 1 && current == *(board + i * size + (j + 1))) return 1;
		}
    	}
    	return 0;
}



void menu(int* board, int size, int* maxScore) 
{    
	int score = 0;
	int highScore = 0;
    	int running = 1;
    	int gameStart = 0; 
    	char choice;

    	printStartGame(*maxScore);

    	while (running)
    	{
        	printBoard(board, size, &score, &highScore);
        	printMenu();

        	do
        	{
            		scanf(" %c", &choice);
        	} while (isspace(choice));

        	if (!gameStart && (choice == 'R' || choice == 'r' || 
                           		choice == 'L' || choice == 'l' || 
                           		choice == 'U' || choice == 'u' || 
                           		choice == 'D' || choice == 'd'))
		{
            		printf("You need to start a game first.\n");
            		continue;
		}

		int moveResult = 0;

        	switch (choice)
        	{
            		case 'N':  
            		case 'n':
                		score = 0;
                		gameStart = newGameButton(board, size);
                		break;

            		case 'E': 
            		case 'e':
                		printf("Ending previous game - your score %d best score %d\n\n", score, highScore);
                		printf("bye bye\n");
                		running = 0;  
                		break;

            		case 'R': 
            		case 'r':
                		moveResult = move(board, size, 'r', &score, &highScore);
                		break;

            		case 'L': 
            		case 'l':
                		moveResult = move(board, size, 'l', &score, &highScore);
                		break;

            		case 'U':  
            		case 'u':
                		moveResult = move(board, size, 'u', &score, &highScore);
                		break;

            		case 'D':  
            		case 'd':
                		moveResult = move(board, size, 'd', &score, &highScore);
                		break;

            		default:
                		printf("Invalid choice. Please try again.\n");
                		break;
		}

        	if (moveResult == 0 && gameStart)
        	{
            		printf("‫‪‫‪Nothing to move in this direction, choose another option.\n");
		}

        	if (gameStart && !hasAvailableMoves(board, size))
        	{
            		printBoard(board, size, &score, &highScore);
            		printf("Game over your score is %d\n\n", score);
            		running = 0;
        	}
        
        	if (isGameOver(board, size, *maxScore))
        	{
            		printf("\n\n");
            		printf("You Won with a score of %d! - Ending Game\n", score);
            		running = 0;
        	}
    	}
}






void playGame(int* board, int size, int scoreToWin)
{
	clearBoard(board , size);
	menu(board, size, &scoreToWin);
}
