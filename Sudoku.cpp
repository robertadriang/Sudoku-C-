#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int counter = 0; ///Used for checking the validity of a solution

bool EmptyPlace(int sudoku[9][9], short& row, short& column)
{
	for (row = 0; row < 9; row++)
		for (column = 0; column < 9; column++)
			if (sudoku[row][column] == 0)
				return true;
	return false;
}

bool RowValid(int sudoku[9][9], short row, short number)
{
	for (short column = 0; column < 9; column++)
		if (sudoku[row][column] == number)
			return true;
	return false;
}

bool ColumnValid(int sudoku[9][9], short column, short number)
{
	for (short row = 0; row < 9; row++)
		if (sudoku[row][column] == number)
			return true;
	return false;
}

bool BoxValid(int sudoku[9][9], int rowStart, int columnStart, int number)
{
	for (int row = 0; row < 3; row++)
		for (int column = 0; column < 3; column++)
			if (sudoku[row + rowStart][column + columnStart] == number)
				return true;
	return false;
}

bool ValidInsertion(int sudoku[9][9], short row, short column, short number)
{
	return (RowValid(sudoku, row, number) == 0 
		&& ColumnValid(sudoku,column,number) == 0 
		&& BoxValid(sudoku,row-row%3,column-column%3,number) == 0 
		&& sudoku[row][column] == 0);
}

bool SolveSudoku(int sudoku[9][9])
{
	short row, column;
	if (EmptyPlace(sudoku, row, column) == 0)
		return true;

	for (short number = 1; number <= 9; number++)
	{
		if (ValidInsertion(sudoku, row, column, number) == 1)
		{
			sudoku[row][column] = number;

			if (SolveSudoku(sudoku) != 0)
				return true;
			
			sudoku[row][column] = 0;
		}
	}
	
	return false;
}

void SolveAllSudoku(int sudoku[9][9])
{
	short row, column;
	if (EmptyPlace(sudoku, row, column) == 0)
		counter++;

	for (short number = 1; number <= 9; number++)
	{
		if (ValidInsertion(sudoku, row, column, number) == 1)
		{
			sudoku[row][column] = number;
			SolveAllSudoku(sudoku);
			sudoku[row][column] = 0;
		}
	}

	//return false;
}

void PrintSolution(int sudoku[9][9])
{
	cout << char(201);
	
	for (int i = 0; i < 23; i++)
		if (i != 7 && i != 15)
			cout << char(205);
		else
		cout << char(203);
	cout << char(187);
	cout << '\n';  /// Drawing the upper line of the sudoku

	for (short i = 0; i < 9; ++i)
	{
		if (i % 3 == 0 && i != 0)
		{
			cout << char(204);
			for (int i = 0; i < 23; i++)
				if (i != 7 && i != 15)
					cout << char(205);
				else
				cout << char(206);
			cout << char(185);
			cout << '\n'; ///The midlines
		}

		cout << char(186)<<" ";
		for (short j = 0; j < 9; ++j)
		{
			if (j % 3 == 0&&j!=0)
				cout << char(186)<<" ";
			cout << sudoku[i][j] <<" ";
			if (j == 8)
				cout << char(186);
		}
		
		cout << '\n';
	}
	cout << char(200);
	for (int i = 0; i < 23; i++)
		if (i == 7 || i == 15)
			cout << char(202);
		else
		cout << char(205);
	cout << char(188);
	cout << '\n';
}

void UnsolveSudoku(int sudoku[9][9],int number)
{
	for (int i = 0; i < number; ++i)
	{
		int row = rand() % 9;
		int column = rand() % 9;
		int aux = sudoku[row][column];
		if (aux != 0)
		{
			sudoku[row][column] = 0;
			SolveAllSudoku(sudoku);
			if (counter != 1)
			{
				sudoku[row][column] = aux;
				i--;
			}
			counter = 0;
		}
		else
			i--;
	}
		
}

int main()
{
	int sudoku[9][9];
	srand((unsigned)time(0));
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			sudoku[i][j] = 0;
	sudoku[rand() % 9][rand() % 9] = rand() % 9 + 1;
	
	cout << "Here's our sudoku base: " << '\n';
	PrintSolution(sudoku);

	cout << "Here is a possible sudoku board fully completed: " << '\n';
	if (SolveSudoku(sudoku) == true)
		PrintSolution(sudoku);
	else
		cout << "There is no valid solution";

	UnsolveSudoku(sudoku,50);
	cout<<"Here is a sudoku board after removing some of the values: "<<'\n';
	PrintSolution(sudoku);

	SolveAllSudoku(sudoku);
	cout << "The number of solutions for this puzzle is always: " << counter;
	return 0;
}