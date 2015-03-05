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

//the set is a 9 array
int[] check_set(int set[])
{
	int number[2] = {0, 0};
	for (int i = 0 ; i < 9 ; i++)
	{
		if(set[i] != 0)
		{
			if(number != 0)
			{
				return(-1);
			}
			number = {set[i], i};
		}
	}
	return(number);
}


//check a case of all possibilities
void check_case(int x, int y, array *possible, array final_grid)
{
	//var
	int set[9];
	int ret_func[2] = {0, 0};

	//creation of the set
	for(int i = 0 ; i < 9 ; i++)
	{
		set[i] = possible[i][x][y];
	}

	//we call the check_set
	ret_func = check_set(set);

	//if the return is positiv, we assign the value in the final_grid
	if (ret_func[0] > 0)
	{
		final_grid[x][y] = ret_func[0];
		//we put a 0 at the [k][x][y]
		possible[ret_func[0] - 1][x][y] = 0;
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		fprintf(stderr, "Value already assigned at [%d][%d]", x, y);
	}
}


//we check a box of ONE possibility
void check_box(int x, int y, array *possible, array final_grid, int the_possibility)
{
	//var
	int set[9];
	int ret_func = {0, 0};
	int k = 0;

	//creation of the set
	for (int i = x ; i < x + 3 ; i++, k++)
	{
		for (int j = y ; j < y + 3 ; j++)
		{
			set[k] = possible[the_possibility][i][j];
		}
	}

	//we call the check_set
	ret_func = check_set(set);

	//if the return is positiv, we assign the value in the final grid
	if (ret_func[0] > 0)
	{
		final_grid[x][y] = ret_func[0];
		//we remove the value in all possibility
		for (int i = 0 ; i < 9 ; i++)
		{
			possible[i][x + ret_func[1] / 3][y + ret_func[1] % 3] = 0;
		}
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
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
