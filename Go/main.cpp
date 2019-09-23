//
//  COMP 2012H Programming Assignment 1: Go
//  Filename: main.cpp
//

#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
#include "Todo.h"
#include "Helper.h"
using namespace std;

int main() {
	srand(time(NULL));			// Initialize pseudo-random number generator

	Stone board[19][19];			// Define a 19x19 2D array for storing the current board data.
	char option = ' ';			// For storing the first option (i.e., read / generate)
	char operation = ' ';		// For storing user's operation
	char filename[256];			// For input and output filename

	int record[1000][2];		// Define a 1000x2 2D array for storing moves of the whole game. For the #n step, row in record[n][0] and column in record[n][1]

	bool ended = false;				// Used to check whether the game is ended
	bool is_last_skipped = false;	// Record whether the last move is skipped.
	bool is_this_skipped = false;	// Record whether this step is skipped.
	Stone winner = Empty;					// Who is the winner.
	Stone current_player = Black;			// The player that can move in this step.
	int counter = 0;				// The counter to record the number of steps.
	int max_steps = 0;
	char a;	
	int b, row, col;				// Used to take the input.

	// Check whether the user wants to read the existing data or
	// generate a brand new Go board

	cout << "Read board file / Generate new empty Go board (R/G)? ";
	cin >> option;

	// If the user wants to read the existing data
	if (option == 'R' || option == 'r') {
		// Get the name of board file
		cout << "Enter the board file name (e.g., board.txt): ";
		cin >> filename;
		// Read data from board file and assign them to
		// the current board
		read_file(board, record, counter, max_steps, filename);
	}
	else {
		// The user wants to generate a new empty board
		initialize_board(board);
	}
	cout << "\n\n";

	do {
		// Change the current player
		current_player = counter % 2 == 0 ? Black:White;

		is_this_skipped = false;

		// Show the current board
		display_board(board);
		cout << endl;
		//display_raw(board);
		//You can enable this statement to debug.

		// Show possible options
		show_options(current_player, counter, max_steps);

		// Get user's input
		cout << "Enter Operation: ";
		cin >> operation;

		// Call different functions according to user's input
		switch (operation) {
		case 'e':
		case 'E':
			cout << "Enter the coordinates of the cell: ";
			cin >> a >> b;
			if (!('A' <= a && a <= 'Z' && 1 <= b && b <= 19)) {
				cout << "\n\nInvalid Input! The input should be like A3, B4, etc.\n" << endl;
				break;
			}
			col = a - 'A';
			row = b - 1;
			switch (edit(board, current_player, row, col, record, counter, max_steps)) {
			case -1:
				cout << "\n\nOut of range!\n" << endl;
				break;
			case -2:
				cout << "\n\nThis cell is occupied!\n" << endl;
				break;
			case -3:
				cout << "\n\nInvalid move. This is suicide.\n" << endl;
				break;
			case 0:
				break;
			}
			break;

		case 's':
		case 'S':
			if (is_last_skipped) ended = true;
			is_this_skipped = true;
			record[counter][0] = -1, record[counter][1] = -1;
			counter++;
			max_steps=counter;
			break;

		case 'g':
		case 'G':
			ended = true;
			winner = switch_player(current_player);
			break;

		case 'o':
		case 'O':
			write_file(record, counter, max_steps);
			break;

		case 'l':
		case 'L':
			cout << "Enter the coordinates of the cell: ";
			cin >> a >> b;
			if (!('A' <= a && a <= 'Z' && 1 <= b && b <= 19)) {
				cout << "\n\nInvalid Input! The input should be like A3, B4, etc.\n" << endl;
				break;
			}
			col = a - 'A';
			row = b - 1;
			{
				bool connected_part[19][19], liberties[19][19];
				fill(&connected_part[0][0], &connected_part[18][18], false);
				fill(&liberties[0][0], &liberties[18][18], false);
				int rv = check_liberties(board, row, col, connected_part, liberties);
				switch (rv){
				case -1:
					cout << "\n\nOut of range!\n" << endl;
					break;
				case -2:
					cout << "\n\nThis cell is empty!\n" << endl;
					break;
				default:
					cout << "\n\nThe number of liberties of the selected stone is " << rv << "\n" << endl;
				}
			}
			break;

		case 'j':
		case 'J':
			cout << "Enter the step you want to jump to: ";
			int tmp;
			cin >> tmp;
			if (tmp < 1 || tmp > max_steps+1) {
				cout << "ERROR: step not exists." << endl;
			}
			else {
				jump_to(board, tmp-1, record, counter, max_steps);
			}
			break;

		case 'q':
		case 'Q':
			ended = true;
			break;

		default:
			cout << "ERROR: Invalid command." << endl;
			break;
		}

		// Update is_last_skipped
		is_last_skipped = is_this_skipped;

		cout << endl;
	} while (!ended);

	if (winner != Empty)
		cout << "Winner is Player" << winner << endl;
	
	return 0;
}
