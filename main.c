//sudoku solver for 9*9 array
#include <stdio.h>
#include <stdlib.h>
//#define DEBUG

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


//the set is a 9 array
void check_set(int set[], int *ret_func)
{
	for (int i = 0 ; i < 9 ; i++)
	{
		if(set[i] != 0)
		{
			if(ret_func[0] != 0)
			{
				ret_func[0] = -1;
				break;
			}
			ret_func[0] = set[i];
			ret_func[1] = i;
		}
	}
}


//check a case of all possibilities
int check_case(int x, int y, array *possible, array final_grid)
{
	//var
	int set[9];
	int ret_func[2] = {0, 0};
	int ret = 0;

	//creation of the set
	for(int i = 0 ; i < 9 ; i++)
	{
		set[i] = possible[i][x][y];
	}

	//we call the check_set
	check_set(set, ret_func);

	//if the return is positiv, we assign the value in the final_grid
	if (ret_func[0] > 0 && final_grid[x][y] == 0)
	{
		#ifdef DEBUG
		fprintf(stdout, "case found ! %d found at [%d][%d].\n", ret_func[0], x, y);
		#endif
		final_grid[x][y] = ret_func[0];
		//we put a 0 at the [k][x][y]
		del_number(ret_func[0], x, y, possible);
		//we increment the return value
		ret++;
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		#ifdef DEBUG
		fprintf(stderr, "Value already assigned at [%d][%d]", x, y);
		#endif
	}
	return(ret);
}


//we check a box of ONE possibility
int check_box(int x, int y, array *possible, array final_grid, int the_possibility)
{
	//var
	int set[9];
	int ret_func[2] = {0, 0};
	int k = 0;
	int ret = 0;

	//creation of the set
	for (int i = x ; i < x + 3 ; i++)
	{
		for (int j = y ; j < y + 3 ; j++, k++)
		{
			set[k] = possible[the_possibility][i][j];
		}
	}

	//we call the check_set
	check_set(set, ret_func);

	//if the return is positiv, we assign the value in the final grid
	if (ret_func[0] > 0 && final_grid[ret_func[1] / 3 + x][ret_func[1] % 3 + y] == 0)
	{
		#ifdef DEBUG
		fprintf(stdout, "box found ! %d found at [%d][%d].\n", ret_func[0], ret_func[1] / 3 + x, ret_func[1] % 3 + y);
		#endif
		final_grid[ret_func[1] / 3 + x][ret_func[1] % 3 + y] = ret_func[0];
		//we remove the value in all possibility
		del_number(ret_func[0], ret_func[1] / 3 + x, ret_func[1] % 3 + y, possible);
		//we increment the return value
		ret++;
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		#ifdef DEBUG
		fprintf(stderr, "Value already assigned at [%d][%d]", x, y);
		#endif
	}
	return(ret);
}

//we check a column of ONE possibility
int check_column(int y, array *possible, array final_grid, int the_possibility)
{
	//var
	int set[9];
	int ret_func[2] = {0, 0};
	int ret = 0;


	//creation of the set
	for (int i = 0 ; i < 9 ; i++)
	{
		set[i] = possible[the_possibility][i][y];
	}

	//we call the check_set
	check_set(set, ret_func);

	//if the return is positiv, we assign the value in the final grid
	if (ret_func[0] > 0 && final_grid[ret_func[1]][y] == 0)
	{
		#ifdef DEBUG
		fprintf(stdout, "column found ! %d found at [%d][%d].\n", ret_func[0], ret_func[1], y);
		#endif
		final_grid[ret_func[1]][y] = ret_func[0];
		//we remove the value in all possibility
		del_number(ret_func[0], ret_func[1], y, possible);
		//we increment the return value
		ret++;
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		#ifdef DEBUG
		fprintf(stderr, "Value already assigned at [%d][%d]\n", ret_func[1], y);
		#endif
	}
	return(ret);
}


//we check a row of ONE possibility
int check_row(int x, array *possible, array final_grid, int the_possibility)
{
	//var
	int set[9];
	int ret_func[2] = {0, 0};
	int ret = 0;


	//creation of the set
	for (int i = 0 ; i < 9 ; i++)
	{
		set[i] = possible[the_possibility][x][i];
	}

	//we call the check_set
	check_set(set, ret_func);

	//if the return is positiv, we assign the value in the final grid
	if (ret_func[0] > 0 && final_grid[x][ret_func[1]] == 0)
	{
		#ifdef DEBUG
		fprintf(stdout, "row found ! %d found at [%d][%d].\n", ret_func[0], x, ret_func[1]);
		#endif
		final_grid[x][ret_func[1]] = ret_func[0];
		//we remove the value in all possibility
		del_number(ret_func[0], x, ret_func[1], possible);
		//we increment the return value
		ret++;
	}
	//if the return is nul, the value is already assigned
	else if (ret_func[0] == 0)
	{
	}
	//else the return is negativ, there is a problem
	else
	{
		#ifdef DEBUG
		fprintf(stderr, "Value already assigned at [%d][%d]", x, ret_func[1]);
		#endif
	}
	return(ret);
}






//initialise final_grid with the input value, return the number of blank box
int given_grid(int *argv[], array final_grid)
{
	int ret = 0;
	//we read the 81's value in argv
	for (int i = 0 ; i < 81 ; i++)
	{	
		//and write it in final_grid
		char *carac = (char *)argv[i + 1];
		int the_number = atoi(carac);
		//we check if the number is between 0 and 9
		if (the_number >= 0 && the_number <= 9)
		{
			//we coun't the number of blank box
			if (the_number == 0)
			{
				ret++;
			}
			final_grid[i / 9][i % 9] = the_number;
		}
		else
		{
			fprintf(stderr, "Error, the number %d should be between 0 and 9.\n", the_number);
			exit(0);
		}
	}
	return(ret);
}
	
void main(int argc, int *argv[])
{
	//var
	array possible[9];
	array final_grid;
	int number_blank = 0;
	int w = 0; //loop number done

	//we check if the input is ok:
	if (argc != 82)
	{
		fprintf(stderr, "%d arguments, usage: x x x x..., where there is 81 x and x is between 0 and 9 (0 for a blank box)./n", argc);
		exit(0);
	}

	//we read the value from the user
	number_blank = given_grid(argv, final_grid);
	printf("Hello world !\n");

	init_possible(possible);
	display(final_grid);
	for (int i = 0 ; i < 81 ; i++)
	{
		del_number((int)final_grid[i / 9][i % 9], i / 9, i % 9, possible);
	}

	//display_possible(possible);


	for (w = 0 ; w < 100 && number_blank > 0 ; w++)
	{
		for (int j = 0 ; j < 9 ; j++)
		{
			for (int i = 0 ; i < 9 ; i++)
			{
				number_blank -= check_row(i, possible, final_grid, j);
				number_blank -= check_column(i, possible, final_grid, j);
				number_blank -= check_case(j, i, possible, final_grid);
			}
		}

		for (int k = 0 ; k < 9 ; k++)
		{
			for (int j = 0 ; j < 9 ; j+= 3)
			{
				for (int i = 0 ; i < 9 ; i+= 3)
				{
					number_blank -= check_box(i, j, possible, final_grid, k);
				}
			}
		}	
	}	

	//display_possible(possible);
	if(w < 100)
	{
		printf("\n\n Solution found in %d round(s) \n", w);
	}
	else
	{
		printf("\n\n Solution not found, %d rounds made, actual numbers found :\n", w);
	}
	printf("\n\n");
	display(final_grid);
}
