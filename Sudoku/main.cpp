#include "Sudoku.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int , char * argv[]) {
	// Reads the puzzle from the expected input file in th current working directory.
	ifstream inputFile("puzzle.txt");

	// Report a missing input file before attempting to solve anything.
	if (!inputFile) {
		cerr << argv[0] << endl;
		cerr << "Error: input file does not exist. Please ensure the input file is stored in the current working directory." << endl;
		return -1;
	}

	// Create the output file that will hold the discovered solutions.
	ofstream outputFile("solution.txt");
	if (!outputFile) {
		cerr << "Error: unable to create the output file 'solution.txt'." << endl;
		inputFile.close();
		return -1;
	}

	Sudoku puzzle; // Stores the puzzle board and its solving state.
	try {
		puzzle.loadData(inputFile); // Read the 16x16 puzzle from the input stream.
		puzzle.verifyBoard(); // Confirm the board contains only legal Sudoku symbols and no duplicates.
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		inputFile.close();
		outputFile.close();
		return -1;
	}

	puzzle.find_All_Solutions(outputFile); // Generate and write every valid solution.

	// Close both files once the solving step has completed.
	inputFile.close();
	outputFile.close();

	return 0;
}