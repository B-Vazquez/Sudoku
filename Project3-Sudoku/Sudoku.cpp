#include "Sudoku.h"
#include <stdexcept>

// Stores the size of the board
const int Sudoku::SIZE = 16;

// Character representing a blank on the board
const char Sudoku::BLANK = '.';

// Array storing all possible values for a given cell
const char Sudoku::HEX_DIGITS[SIZE] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

// Constructor
Sudoku::Sudoku() : num_of_solutions(0) {
	board = new char* [SIZE];
	for (int row = 0; row < SIZE; row++) {
		board[row] = new char[SIZE];
	}
}

// Copy constructor
Sudoku::Sudoku(const Sudoku& other) {
	board = NULL;
	*this = other;
}

// Destructor
Sudoku::~Sudoku() {
	for (int row = 0; row < SIZE; row++) {
		delete[] board[row];
	}
	delete[] board;
}

// Deep-copy assignment operator
const Sudoku& Sudoku::operator = (const Sudoku& rhs) {
	if (this != &rhs) {
		if (board) {
			for (int row = 0; row < SIZE; row++) {
				delete[] board[row];
			}
			delete[] board;
			board = NULL;
		}
		num_of_solutions = rhs.num_of_solutions;
		board = new char* [SIZE];
		for (int row = 0; row < SIZE; row++) {
			board[row] = new char[SIZE];
			for (int col = 0; col < SIZE; col++) {
				board[row][col] = rhs.board[row][col];
			}
		}
	}
	return *this;
}

/*	Loads the board stored in input stream into the board 
	@param in: An input stream
*/
void Sudoku::loadData(istream& in) {
	string currentLine;
	for (int row = 0; row < SIZE; row++) {
		if (!getline(in, currentLine) || currentLine.size() != SIZE) {
			throw std::runtime_error("Error: Input file does not contain a valid board. The board should be a 16x16 grid consisting of '.' and hexadecimal digits.");
		}
		for (int col = 0; col < SIZE; col++) {
			board[row][col] = currentLine[col];
		}
	}
}

/* Verifies the board loaded from the input stream.
*/
void Sudoku::verifyBoard() {
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			char currentChar = board[row][col];
			bool validChar = (currentChar == BLANK);

			if (!validChar) {
				for (int digit = 0; digit < SIZE; digit++) {
					if (currentChar == HEX_DIGITS[digit]) {
						validChar = true;
						break;
					}
				}
			}
			if (!validChar) {
				throw std::runtime_error("Error: Input file does not contain a valid board. The board should be a 16x16 grid consisting of '.' and hexadecimal digits.");
			}
			if (currentChar != BLANK) {
				if (inSameRow(row, currentChar, col) || inSameCol(col, currentChar, row) || inSameGrid(row, col, currentChar)){
					throw std::runtime_error("Error: Input file contains a board with duplicate values in a row/column/grid.");
				}
			}
		}
	}
}

/*	Row index of the next cell (row-major order).
	@param row: The current row
	@param col: The current column
	@return: The row of the next cell
*/
int Sudoku::nextRowIndex(int row, int col) const {
	if (row == SIZE - 1 && col == SIZE - 1) { return -1; }
	if (col == SIZE - 1) { return row + 1; }
	else { return row; }
}

/*	Column index of the next cell (row-major order).
	@param row: The current row
	@param col: The current column
	@return: The column of the next cell
*/
int Sudoku::nextColIndex(int row, int col) const {
	if (row == SIZE - 1 && col == SIZE - 1) { return -1; }
	if (col == SIZE - 1) { return 0; }
	else { return col + 1; }
}

/*	Test if a digit already appears in a row.
	@param row: The current row
	@param digit: The digit to check for
	@param currCol: The column of the current digit
	@return: True if the digit is found in the current row, false if it is not
*/
bool Sudoku::inSameRow(int row, char digit, int currCol) const {
	for (int col = 0; col < SIZE; col++) {
		if (board[row][col] == digit && col != currCol) {
			return true;
		}
	}
	return false;
}

/*	Test if a digit already appears in a column.
	@param col: The current column
	@param digit: The digit to check for
	@param currRow: The row of the current diggit
	@return: True if the digit is found in the current column, false if it is not
*/
bool Sudoku::inSameCol(int col, char digit, int currRow) const {
	for (int row = 0; row < SIZE; row++) {
		if (board[row][col] == digit && row != currRow) {
			return true;
		}
	}
	return false;
}

/*	Test if a digit already appears in a 4-by-4 grid.
	@param row: The current row
	@param col: The current column
	@param digit: The digit to check for
	@return: True if the digit is found in the 4-by-4 grid, false if it is not
*/
bool Sudoku::inSameGrid(int row, int col, char digit) const {
	int gridStartRow = row / 4 * 4, gridStartCol = col / 4 * 4;
	for (int i = gridStartRow; i < gridStartRow + 4; i++) {
		for (int j = gridStartCol; j < gridStartCol + 4; j++) {
			if (board[i][j] == digit && (i != row && j != col)) {
				return true;
			}
		}
	}
	return false;
}

/*	Writes the current solution to the output stream
	@param out: An output stream
*/
void Sudoku::printSolution(ostream& out) {
	out << "Solution " << ++num_of_solutions << endl << endl;
	for (int row = 0; row < SIZE; row++) {
		for (int col = 0; col < SIZE; col++) {
			out << board[row][col];
		}
		out << endl;
	}
	out << endl;
}

/*	Finds all possible solutions for the given board
	@param row: The current row
	@param col: The current column
	@param out: An output stream
*/
void Sudoku::find_All_Solutions(int row, int col, ostream& out) {
	if (row == -1 || col == -1) { // Base case
		printSolution(out); // Solution found
		return;
	}
	if (board[row][col] != BLANK) {
		// Cell is not blank
		find_All_Solutions(nextRowIndex(row, col), nextColIndex(row, col), out);
	}
	else {
		// Cell is blank
		for (int i = 0; i < SIZE; i++) {
			char digit = HEX_DIGITS[i];

			if (inSameRow(row, digit, col)) { continue; }
			if (inSameCol(col, digit, row)) { continue; }
			if (inSameGrid(row, col, digit)) { continue; }

			// Fill the cell with the current digit
			board[row][col] = digit;

			find_All_Solutions(nextRowIndex(row, col), nextColIndex(row, col), out);

			board[row][col] = BLANK;
		}
	}
}

// Wrapper function
void Sudoku::find_All_Solutions(ostream& out){
	find_All_Solutions(0, 0, out);
}