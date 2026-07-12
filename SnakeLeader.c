#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>


/* ============================================================================
 * Project: Snake and Ladder Simulation
 * Description: A terminal-based game simulation tracking stats across multiple games.
 * Author: Faisal Alshathri
 * Purpose: A portfolio project to practice C programming, specifically 
 *          focusing on pointers, 2D arrays, and statistical simulation.
 * Features:
 * - Print board (2D array)
 * - Place snakes and ladders (fixed and random locations)
 * - Dice rolling function
 * - Play function (board movement logic)
 * - Winning condition evaluation
 * - Automated play simulation
 * - Testing cases
 *
 * Concepts & Terminology Applied:
 * - Functions
 * - 2D Arrays
 * - Pointers (Pass by reference vs. Pass by value)
 * - Time & Sleep functions
 * - Random number generation
 * - Modulo operator
 * ========================================================================= */


void initiBoard(int size, int board[][size]);
void printBoard(char * playerName1, char * playerName2, int size, int board[][size], int x1, int y1, int x2, int y2);
void printGrid(char * playerName, int size, int board[][size], int x, int y);


int rollDice();
bool play(char * playerName, int * playerX, int * playerY, int size, int dice);

void simulation(int game_number, int size, int board[][size]);

int main(void)
{
	//Seed the random number generator using the current time
	srand(time(NULL));

	const int size = 10;
	int board[size][size];

	int x = 0,y = size - 1;  //player1

	int xx = 0,yy = size - 1;  //player2


	printf("Snakes and Ladder Game\n\n");
	initiBoard(size, board);
	printGrid("[Start]", size, board, x, y);

	int count = 0;
	bool keep_playing = true;

	printf("press 'p' to play game or 's' for simulation:\n");
	char s;
	scanf("%c", &s);
	getchar();
	if (s == 's' || s == 'S')
	{
		simulation(2, size, board);

	}
	else
	{
		char * playerName1 = "[P1]";
		char * playerName2 = "[P2]";
		do
		{

			printf("Press Enter to roll dice!('q' to quit):\n");
			char q = getchar();
			if (q == 'q' || q == 'Q')
			{
				keep_playing = false;
				break;
			}
			//getchar();
			int d = rollDice();
			count++;
			printf("Player1 dice:%d\n", d);
			keep_playing = play(playerName1, &x, &y, size, d);
			printBoard(playerName1, playerName2, size, board, x, y, xx, yy);
			if (!keep_playing)
			{
				printf("\nPlayer 1 win game\n");
				printf("\nGame Stats, number of moves %d \n", count);
				break;
			}
			printf("Press Enter to roll dice!('q' to quit):\n");
			q = getchar();
			d = rollDice();
			printf("Player2 dice:%d\n", d);
			keep_playing = play(playerName2, &xx, &yy, size, d);
			printBoard(playerName1, playerName2, size, board, x, y, xx, yy);

			if (!keep_playing)
			{
				printf("\nPlayer 2 win game\n");
				printf("\nGame Stats, number of moves %d \n", count);
			}



		} while (keep_playing);
	}

	return 0;
}




void initiBoard(int size, int board[][size])
{


	int c = 100;

	for (int i = 0; i < size; ++i)
	{
		if (i % 2 == 0) // even row
			for (int j = 0; j < size; j++)
				board[i][j] = c--;
		else // odd row to init increment row
			for (int j = size - 1; j >= 0; j--)

				board[i][j] = c--;


	}

	//fixed

	board[size - 1][1] = 999;  //ladder to up 1 row to 18
	board[0][1] = -999;  //snake down two rows to 80

	board[5][3] = 999;  //ladder to up 1 row to 66
	board[4][size - 1] = -999;  //down two rows to 33

	//add random location ladders/snakes with condition no first or last grid



}

void printGrid(char * playerName, int size, int board[][size], int x, int y)
{

	//printing
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == y && j == x)
				printf("%s\t", playerName);  //your/computer position
			else if (board[i][j] == 999)
				printf("[Ladder] ");
			else if (board[i][j] == -999)
				printf("[Snake] ");
			else
				printf("%d\t", board[i][j]);

		}


		printf("\n\n");

	}


}

void printBoard(char * playerName1, char * playerName2, int size, int board[][size], int x1, int y1, int x2, int y2)
{



	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == y1 && j == x1)
				printf("%s\t", playerName1);  //your/computer position
			else if (i == y2 && j == x2)
				printf("%s\t", playerName2);
			else if (board[i][j] == 999)
				printf("[Ladder] ");
			else if (board[i][j] == -999)
				printf("[Snake] ");
			else
				printf("%d\t", board[i][j]);

		}


		printf("\n\n");

	}



}


int rollDice(void)
{

	return rand() % 6 + 1;

}


bool play(char * playerName, int * playerX, int * playerY, int size, int dice)
{




	if (*playerY % 2 != 0)
	{ //odd row# walk to right
		printf("%s walking to right\n", playerName);
		if (*playerX + dice >= size)
		{
			*playerX = size - (*playerX + dice - size + 1);
			//printf("*playerX:%d\n", *playerX);
			if (*playerY > 0)
				(*playerY)--;

		}
		else
			*playerX += dice;

	}
	else
	{ // even row, walk to left
		printf("%s walking to left\n", playerName);
		if (*playerX - dice < 0)
		{ //if less than zero, go up by reducing Y by 1 then reminder walk to left
			*playerX = (*playerX - dice) < 0?-1 * (*playerX - dice + 1):*playerX - dice;
			if (*playerY > 0)
				(*playerY)--;
			else if (*playerY == 0) //end of game
				*playerX = 0;


		}
		else
			*playerX -= dice;
	}



	//Ladder
	if (*playerY == size - 1 && *playerX == 1)
	{
		printf("Ladder moving to grid 18\n");
		*playerY = size - 2;
		*playerX = 2;
		printf("playerY:%d\n", *playerY);
	}

	//Ladder
	if (*playerY == 5 && *playerX == 3)
	{
		printf("Ladder moving to grid 66\n");
		*playerY = 3;
		*playerX = 5;
		printf("playerY:%d\n", *playerY);
	}

	//Snake
	if (*playerY == 0 && *playerX == 1)
	{
		printf("Snake moving to grid 80\n");
		*playerY = 2;
		*playerX = 0;
		printf("playerY:%d\n", *playerY);
	}

	//Snake
	if (*playerY == 4 && *playerX == 9)
	{
		printf("Snake moving to grid 33\n");
		*playerY = 6;
		*playerX = 7;
		printf("playerY:%d\n", *playerY);
	}


	//End of game
	if (*playerY == 0 && *playerX <= 0)
	{
		*playerX = 0;
		*playerY = 0;
		printf("end of game\n");
		return false;
	}


	return true;



}


void simulation(int game_number, int size, int board[][size])
{

	int x = 0;
	int y = size - 1;
	int dice;
	int count = 0;
	char * playerName = "[ P ]";

	printf("***starting game simulation***\n");
	_sleep(2);
	for (int k = 0; k < game_number; ++k)
	{
		x = 0;
		y = size - 1;
		initiBoard(size, board);
		//system("cls");//clear screen
		printf("starting game %d\n", k + 1);
		for (int i = 0; i < 100; i++)
		{
			dice = rollDice();
			count++;
			printf("dice:%d\n", dice);
			if (!play(playerName, &x, &y, size, dice))
				break;

			printGrid("[P]", size, board, x, y);

			printf("\n");
			_sleep(2);
		}
		printGrid("[P]", size, board, x, y);
	}

	printf("Number of games played:%d\n", game_number);

	printf("Total dice rolls:%d\n", count);
	printf("Average rolls per game:%.2f\n", (float)count / game_number);



}
