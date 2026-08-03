#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::endl;
using std::string;
using std::getline;

class Sudoku {
public:
	// Constructors
	Sudoku(); // Default constructor
	Sudoku(const Sudoku&); // Copy constructor

	// Destructor
	~Sudoku();

	// Class-member Functions
	const Sudoku& operator = (const Sudoku&); // Assignment operator
	void loadData(istream&); // Read in the puzzle from an input stream
	void verifyBoard(); // Verify the board loaded from the input stream
	void find_All_Solutions(ostream&); // Wrapper function

private:
	// Data fields
	char** board; // Row-major dynamic array used to store the 16x16 puzzle grid.
	static const char HEX_DIGITS[]; // Legal symbols for a valid hexadecimal Sudoku cell.
	static const int SIZE; // Number of rows and columns in the puzzle.
	static const char BLANK; // Symbol used to represent an empty cell.
	unsigned int num_of_solutions; // Number of solutions written to the output stream.

	// Class-member Functions
	int nextRowIndex(int, int) const; // Row index of the next cell (row-major order).
	int nextColIndex(int, int) const; // Column index of the next cell (row-major order).
	bool inSameRow(int, char, int) const; // Test if a digit already appears in a row.
	bool inSameCol(int, char, int) const; // Test if a digit already appears in a columns
	bool inSameGrid(int, int, char) const; // Test if a digit already appears in a 3-by-3 grid.
	void find_All_Solutions(int, int, ostream&); // Find all solutions for the given board
	void printSolution(ostream&); // Writes the current solution to the output stream
};

#endif