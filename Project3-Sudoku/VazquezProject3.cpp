#include "Sudoku.h"

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	// Opens input file
	ifstream inputFile("puzzle.txt");

	// Checks if the input file was opened successfully
	if (!inputFile) {
		cout << argv[0] << endl;
		cout << "Error: input file does not exist. Please encure the input file is stored in the above directory." << endl;
		return -1;
	}
	// Opens/creates the output file
	ofstream outputFile("solution.txt");


	Sudoku puzzle; // Object that stores and solves a sudoku board
	try{
		puzzle.loadData(inputFile); // Passes the input file into function 'loadData' to store the given sudoku board
		puzzle.verifyBoard(); // Verifies the board loaded from the input file.
	}
	catch (const exception& e){
		outputFile << e.what() << endl;
		inputFile.close();
		outputFile.close();
		return -1;
	}
	puzzle.find_All_Solutions(outputFile); // Calls function 'find_All_Solutions' to find all solutions and write them to the given output file

	// Closes the input and output file
	inputFile.close();
	outputFile.close();

	return 0;
}