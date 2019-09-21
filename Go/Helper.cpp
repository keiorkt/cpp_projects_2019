//
//  COMP 2012H Programming Assignment 1: Go
//  Filename: helper.cpp
//

#include "Helper.h"
#include "Todo.h"

/***********************************************************************
 * Get the other player.
 ***********************************************************************/

Stone switch_player(Stone p) {
	return Stone(3 - int(p));
}

/***********************************************************************
 * Initialize the board.
 ***********************************************************************/

void initialize_board(Stone board[][19]) {
	for (int row = 0; row < 19; row++) {
		for (int col = 0; col < 19; col++)
			board[row][col] = Empty;
	}
}

/***********************************************************************
 * Ask the user to input a filename, read board data from
 * that file, and store them in an array.
 ***********************************************************************/

void read_file(Stone board[][19], int record[][2], int& counter, int& max_steps, const char filename[]) {
	// Define ifstream object
	ifstream fin;

	// Open file with error checking
	fin.open(filename);
	if (fin.fail()) {
		cout << "Failed opening board file." << endl;
		exit(1);
	}

	// Read board data from the file and put them into the array
	fin >> counter >> max_steps;

	for (int i = 0; i < max_steps; ++i) {
		fin >> record[i][0] >> record[i][1];
	}

	jump_to(board, counter, record, counter, max_steps);

	// Close the file
	fin.close();
}

/***********************************************************************
 * Ask the user to input a filename, write board data into
 * that file.
 ***********************************************************************/

void write_file(const int record[][2], const int counter, const int max_steps) {
	// Define ifstream object
	ofstream fout;

	// Get the name of board file
	char filename[256];
	cout << "Enter the board file name (e.g., board.txt): ";
	cin >> filename;
	
	fout.open(filename);

	fout << counter << " " << max_steps << endl;

	// Write board data into the file.
	for (int i = 0; i < max_steps; ++i) {
		fout << record[i][0] << " " << record[i][1] << endl;
	}

	// Close the file
	fout.close();
}

/***********************************************************************
 * Translate the stored board data into character.
 ***********************************************************************/

char translate(Stone cell) {
	switch (cell) {
	case Empty:
		return ' ';
	case Black:
		return '#';
	case White:
		return 'o';
	}
}

/***********************************************************************
 * Display the current board data on screen.
 ***********************************************************************/

void display_board(const Stone board[][19]) {
	// Display column header
	cout << "   A B C D E F G H I J K L M N O P Q R S" << endl;

	// Display board data
	for (int row = 0; row < 19; row++) {
		cout << row + 1 << " ";
		if (row + 1 < 10) cout << " ";
		for (int col = 0; col < 19; col++) {
			char ch = translate(board[row][col]);
			cout << ch;
			if (col != 18)
				cout << "-";
		}
		cout << endl;
		if (row != 18)
			cout << "   | | | | | | | | | | | | | | | | | | |" << endl;
	}
}

/***********************************************************************
 * Display the raw board data on screen.
 ***********************************************************************/

void display_raw(const Stone board[][19]) {
	for (int row = 0; row < 19; ++row) {
		for (int col = 0; col < 19; ++col) {
			cout << board[row][col];
		}
		cout << endl;
	}
	cout << endl;
}

/***********************************************************************
 * Show options
 ***********************************************************************/

void show_options(Stone player, int counter, int max_step) {
	cout << "This is step #" << counter+1 << "/" << max_step+1 << endl;
	cout << "This is the step of Player " << player << endl;
	cout << "\n\n";
	cout << "Options:" << endl
		<< "   E:  Edit cell" << endl
		<< "   S:  Skip this step" << endl
		<< "   G:  Give up" << endl
		<< "   O:  Output the current board into a file" << endl
		<< "   L:  Check the number of liberties of a stone" << endl
		<< "   J:  Jump to specified step" << endl
		<< "   Q:  Quit" << endl
		<< endl;
}