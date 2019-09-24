//
//  COMP 2012H Programming Assignment 1: Go
//  Filename: todo.cpp
//

#include "Helper.h"
#include "Todo.h"
#include <algorithm>

using std::fill;

/***********************************************************************
 * TODO_1: Check the number of liberties of a given stone. Mark the
 * connected stones and liberties, and return the number of liberties.
 * 
 * - Check whether the input row and column number is out-of-bounds. 
 * 	 If so, return -1 and do nothing.
 * - Check whether the intersection is empty. If so, return -2 and do 
 *   nothing.
 * - Identify the connected part that the selected stone belongs to, 
 *   find and count the number of liberties. Set the corresponding 
 *   elements in connected_part or liberties to be true for any found 
 *   connected stones or liberties.
 ***********************************************************************/

bool out_of_board(int row, int col) {
	return (row < 0 || row > 19 || col < 0 || col > 19);
}

bool in_board(int row, int col) {
	return !(row < 0 || row > 19 || col < 0 || col > 19);
}

void connected_part_rec(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19], int selected_color);
void fill_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19], int selected_color);

int check_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19]) {
	if (out_of_board(row, col)) {
		return -1;
	} else if (!board[row][col]) {
		return -2;
	}

	connected_part_rec(board, row, col, connected_part, liberties, board[row][col]);

	fill_liberties(board, row, col, connected_part, liberties, board[row][col]);

	int numOfConnected = 0;
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			numOfConnected += connected_part[i][j];
		}
	}

	int numOfLiberties = 0;
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			numOfLiberties += liberties[i][j];
		}
	}

	return numOfLiberties;
}

void fill_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19], int selected_color) {
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			if (board[i][j] == selected_color || connected_part[i][j]) {
				if (in_board(i-1, j) && !board[i-1][j]) {
					liberties[i-1][j] = true;
				}

				if (in_board(i, j+1) && !board[i][j+1]) {
					liberties[i][j+1] = true;
				}

				if (in_board(i+1, j) && !board[i+1][j]) {
					liberties[i+1][j] = true;
				}

				if (in_board(i, j-1) && !board[i][j-1]) {
					liberties[i][j-1] = true;
				}
			}
		}
	}
}

void connected_part_rec(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19], int selected_color) {
	if (in_board(row-1, col) && board[row-1][col] == selected_color && !connected_part[row-1][col]) {
		connected_part[row-1][col] = true;
		connected_part_rec(board, row-1, col, connected_part, liberties, selected_color);
	}

	if (in_board(row, col+1) && board[row][col+1] == selected_color && !connected_part[row][col+1]) {
		connected_part[row][col+1] = true;
		connected_part_rec(board, row, col+1, connected_part, liberties, selected_color);
	}

	if (in_board(row+1, col) && board[row+1][col] == selected_color && !connected_part[row+1][col]) {
		connected_part[row+1][col] = true;
		connected_part_rec(board, row+1, col, connected_part, liberties, selected_color);
	}

	if (in_board(row, col-1) && board[row][col-1] == selected_color && !connected_part[row][col-1]) {
		connected_part[row][col-1] = true;
		connected_part_rec(board, row, col-1, connected_part, liberties, selected_color);
	}

	return;
}

/***********************************************************************
 * TODO_2: Check whether a player has captured stones, and mark them.
 * 
 * - Check the whole game board for any captured stones of the selected 
 *   player. Set the corresponding elements in captured to be true. 
 *   Return true if and only if there are any captured stones.
 ***********************************************************************/

bool find_captured(const Stone board[][19], Stone player, bool captured[][19]) {
	bool haveCaptured = false;
	for (int row = 0; row < 19; ++row) {
		for (int col = 0; col < 19; ++col) {
			if (board[row][col] == player) {
				bool connected_part[19][19], liberties[19][19];
				fill(&connected_part[0][0], &connected_part[18][18], false);
				fill(&liberties[0][0], &liberties[18][18], false);
				int numOfLiberties = check_liberties(board, row, col, connected_part, liberties);
				if (!numOfLiberties) {
					captured[row][col] = true;
					haveCaptured = true;
				}
			}
		}
	}
	return haveCaptured;
}

/***********************************************************************
 * TODO_3: Check whether the move is valid and edit the board.
 * 
 * - Check whether the input row and column number is out-of-bounds. If 
 *   so, return -1 and do nothing.
 * - Check whether the intersection is occupied. If so, return -2 and do 
 *   nothing.
 * - Check whether this is suicide. If so, return -3 and do nothing. 
 * - Modify board, including both adding the stone and removing captured
 *   stones if applicable. Update record and return 0.
 * - Append the current move to the record. You need to set counter and 
 *   max_steps correctly.
 ***********************************************************************/

int edit(Stone board[][19], Stone player, int row, int col, int record[][2], int& counter, int& max_steps) {
	if (out_of_board(row, col)) {
		return -1;
	}

	if (board[row][col]) {
		return -2;
	}

	board[row][col] = player;

	bool connected_part[19][19], liberties[19][19], captured[19][19];
	fill(&connected_part[0][0], &connected_part[18][18], false);
	fill(&liberties[0][0], &liberties[18][18], false);
	fill(&captured[0][0], &captured[18][18], false);

	int numOfLiberties = check_liberties(board, row, col, connected_part, liberties);

	if (numOfLiberties == 0) {
		board[row][col] = Empty;
		return -3;
	}

	bool haveCaptured = find_captured(board, player, captured);
	if (haveCaptured) {
		for (int i = 0; i < 19; ++i) {
			for (int j = 0; j < 19; ++j) {
				if (captured[i][j]) {
					board[i][j] = Empty;
				}
			}
		}
	}

	record[counter][0] = row;
	record[counter][1] = col;

	++counter;
	++max_steps;

	return 0;
}

/***********************************************************************
 * TODO_4: Jump to the given step of the game.
 * 
 * - Set the board to the state at target step, and correctly set the 
 *   value of counter and max_steps.
 ***********************************************************************/

void jump_to(Stone board[][19], int target, int record[][2], int& counter, int& max_steps) {
	
}
