//sudoku solver for 9*9 array
#include <stdio.h>
#include <stdlib.h>

typedef int line[9];
typedef line array[9];

/**
position :
     __________________
0:  |0|1|2|3|4|5|6|7|8|
    |------------------
1:  |0|1|2|3|4|5|6|7|8|
    |------------------
2:  |0|1|2|3|4|5|6|7|8| 
    |------------------
3:  |0|1|2|3|4|5|6|7|8|
    |------------------
4:  |0|1|2|3|4|5|6|7|8|
    |------------------
5:  |0|1|2|3|4|5|6|7|8|
    |------------------
6:  |0|1|2|3|4|5|6|7|8|
    |------------------
7:  |0|1|2|3|4|5|6|7|8|
    |------------------
8:  |0|1|2|3|4|5|6|7|8|
    ___________________


possible[i][j][k];
k = array number
i = x
j = y

**/

void check_line(int line[])
{
	int alphabet[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
}		


void display(array the_array)
{
	printf("|-----------------|\n");
	for (int i = 0 ; i < 9 ; i++)
	{
		printf("|");
		for (int j = 0 ; j < 9 ; j++)
		{
			printf("%d", the_array[i][j]);
			if (j < 8)
			{
				printf(" ");
			}
		}
		printf("|\n");
	}
	printf("|-----------------|\n\n");
}


/*void display_possible(array *possible)
{
	
	for (int k = 0 ; k < 9 ; k++)
	{
		printf("Possibility %d:\n", k);
		display(possible[k]);
	}
}*/

//initialisation of possible array
void init_possible(array *possible)
{
	//initialisation of all posibilities
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
}


void del_number(int number, int x, int y, array *possible)
{
	//clean the box[x][y] of all possibles array
	for (int k = 0 ; k < 9 ; k++)
	{
		possible[x][y][k] = 0;
	}

	//clean the vertical boxes
	for (int i = 0 ; i < 9 ; i++)
	{
		possible[i][y][number - 1] = 0;
	}

	//clean the horizontal boxes
	for (int j = 0 ; j < 9 ; j++)
	{
		possible[x][j][number - 1] = 0;
	}

	//clean the 3*3 box
	int l = 0, m = 0;
	if (x < 3)
	{
		l = 0;
	}
	else if (x < 6)
	{
		l = 3;
	}
	else
	{
		l = 6;
	}

	if (y < 3)
	{
		m = 0;
	}
	else if (y < 6)
	{
		m = 3;
	}
	else
	{
		m = 6;
	}

	
	for (int cmp = l ; cmp < l + 3 ; cmp++)
	{
		for (int cmp2 = m ; cmp2 < m + 3 ; cmp2++)
		{
			possible[cmp][cmp2][number - 1] = 0;
		}
	}
		
}


void given_grid(int *argv[], array final_grid)
{
	int *ptr_final_grid = &final_grid[0][0];
	for (int i = 1 ; i < 82 ; i++)
	{
		*(ptr_final_grid + (i - 1) * sizeof(int)) = atoi((char *)argv[i]);
	}
}
	
void main(int argc, int *argv[])
{
	//var
	array possible[9];
	array final_grid;

	//we check if the input is ok:
	if (argc != 82)
	{
		fprintf(stderr, "%d arguments, usage: x x x x..., where there is 81 x and x is between 0 and 9 (0 for a blank box)./n", argc);
		exit(0);
	}

	//we read the value from the user
	given_grid(argv, final_grid);
	printf("Hello world !\n");

	init_possible(possible);
	del_number(7, 5, 8, possible);
	//display_possible(possible);
	display(final_grid);
}
