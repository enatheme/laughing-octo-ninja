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


//check a case of all possibilities
void check_case(int x, int y, array *possible, array final_grid)
{
	//var
	int tmp_number = 0;

	//creation of the set
	for(int i = 0 ; i < 9 ; i++)
	{
		if (set[i] != 0)
		{
			if (tmp_number != 0)
			{
				tmp_number = -1;
				i = 10;
			}
			tmp_number = set[i];
		}
	}

	//if the return is positiv, we assign the value in the final_grid
	if (tmp_number > 0)
	{
		final_grid[x][y] = tmp_number;
		//we put a 0 at the [k][x][y]
		possible[tmp_number - 1][x][y] = 0;
	}
	//if the return is nul, the value is already assigned
	else if (tmp_number == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		fprintf(stderr, "Value already assigned at [%d][%d]", x, y);
	}
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


void display_possible(array *possible)
{
	
	for (int k = 0 ; k < 9 ; k++)
	{
		printf("Possibility %d:\n", k);
		display(possible[k]);
	}
}

//initialisation of possible array
void init_possible(array *possible)
{
	array tmp_possible;
	for (int k = 0 ; k < 9 ; k++)
	{
		for (int i = 0 ; i < 9 ; i++)
		{
			for (int j = 0 ; j < 9 ; j++)
			{
				possible[k][i][j] = k + 1;
			}
		}
	}
}


void del_number(int number, /* vertical */ int x, /* horizontal */ int y, array *possible)
{
	if (number != 0)
	{
		//clean the box[x][y] of all possibles array
		for (int k = 0 ; k < 9 ; k++)
		{
			possible[k][x][y] = 0;
		}

		//clean the vertical boxes
		for (int i = 0 ; i < 9 ; i++)
		{
			possible[number - 1][x][i] = 0;
		}
	
		//clean the horizontal boxes
		for (int j = 0 ; j < 9 ; j++)
		{
			possible[number - 1][j][y] = 0;
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
				possible[number - 1][cmp][cmp2] = 0;
			}
		}
	}		
}


//initialise final_grid with the input value
void given_grid(int *argv[], array final_grid)
{
	//we read the 81's value in argv
	for (int i = 0 ; i < 81 ; i++)
	{	
		//and write it in final_grid
		char *carac = (char *)argv[i + 1];
		int the_number = atoi(carac);
		//we check if the number is between 0 and 9
		if (the_number >= 0 && the_number <= 9)
		{
			final_grid[i / 9][i % 9] = the_number;
		}
		else
		{
			fprintf(stderr, "Error, the number %d should be between 0 and 9.\n", the_number);
			exit(0);
		}
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
	display(final_grid);
	for (int i = 0 ; i < 81 ; i++)
	{
//		printf("%d : %d-%d\n", final_grid[i / 9][i % 9], i / 9, i % 9);
//		display(final_grid);
		del_number((int)final_grid[i / 9][i % 9], i / 9, i % 9, possible);
	}

//del_number(7, 5, 8, possible);
	display_possible(possible);
	printf("\n\n");
	display(final_grid);
}
