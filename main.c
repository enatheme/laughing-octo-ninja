//sudoku solver for 9*9 array
#include <stdio.h>
#include <stdlib.h>

typedef int line[9];
typedef line array[9];

void check_line(int line[])
{
	int alphabet[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}		

void display(array *possible)
{
	for (int k = 0 ; k < 9 ; k++)
	{
		printf("%d possibility :\n|-----------------|\n", k + 1);
		for (int i = 0 ; i < 9 ; i++)
		{
			printf("|");
			for (int j = 0 ; j < 9 ; j++)
			{
				printf("%d", possible[i][j][k]);
				if (j < 8)
				{
					printf(" ");
				}
			}
			printf("|\n");
		}
		printf("|-----------------|\n\n");
	}
}

void main(int argc, int argv)
{
	printf("Hello world !\n");
	//initialisation of all posibilities
	array possible[9];
	for (int i = 0 ; i < 9 ; i++)
	{
		for (int j = 0 ; j < 9 ; j++)
		{
			for (int k = 0 ; k < 9 ; k++)
			{
				possible[i][j][k] = k + 1;
			}
		}
	}
	display(possible);
}
