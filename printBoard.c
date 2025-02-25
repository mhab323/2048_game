#include <stdio.h>
#include "printBoard.h"

void clearBoard(int* board, int size)
{
	for (int i = 0; i < size; i++)
	{        
		for (int j = 0; j < size; j++) 
		{
			*(board+size*i+j) = 0;
		}
	}
}

void printBoard(const int *board, int size, int* score , int* highScore) 
{
	int cellWidth = 5; 
	int i, j, k;

	printf("\n\n\n");
    
	printf("Score %d Best %d\n\n", *score , *highScore);

	for (i = 0; i < size; i++) 
    	{
        	for (j = 0; j < size * cellWidth; j++) 
        	{
			printf("-");
        	}
		printf("-\n");

        	for (k = 0; k < size; k++) 
        	{
            		printf("|");
            		if (*(board + size * i + k) == 0) 
            		{
                		for (int p = 0; p < cellWidth - 1; p++) 
        			{
                    			printf(" ");
                		}
            		} 
            		else 
			{		
                		int num = *(board + size * i + k);
                		int numWidth = 0;

				while (num > 0) 
	                	{
					numWidth++;
					num /= 10;
	                	}

	                	int padding = cellWidth - numWidth - 1;
	                	int leftPadding = padding / 2;
	                	int rightPadding = padding - leftPadding;
	
	                	for (int p = 0; p < leftPadding; p++) 
	                	{
					printf(" ");
	                	}
	                	printf("%d", *(board + size * i + k));
	
	                	for (int p = 0; p < rightPadding; p++) 
	                	{
					printf(" ");
	                	}
			}		
		}
	printf("|\n");
	}

	for (i = 0; i < size * cellWidth; i++) 
    	{
		printf("-");
    	}
    	printf("-\n");
    	printf("\n\n\n");
}





void printMenu()
{
	printf("Please choose one of the following options: \n");
	printf("N/n - New Game\n");
	printf("R/r - Move Right\n");
	printf("L/l - Move Left\n");
	printf("U/u - Move Up\n");
	printf("D/d - Move Down\n");
	printf("E/e - Exit\n");
	printf("\nEnter your choice\n");
}


void printStartGame(int maxScore)
{
	
	printf("---------------- STARTING GAME ----------------\n");
	printf("\t     Highest tile to win %d\n", maxScore);
	printf("-----------------------------------------------\n");
	
}



