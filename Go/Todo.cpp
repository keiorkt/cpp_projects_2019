//
//  COMP 2012H Programming Assignment 1: Go
//  Filename: todo.cpp
//

#include "Helper.h"
#include "Todo.h"
#include <algorithm>

using std::fill;

bool out_of_board(int row, int col) {
	return (row > 18 || row < 0 || col > 18 || col < 0);
}

bool in_board(int row, int col) {
	return !(row > 18 || row < 0 || col > 18 || col < 0);
}

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

void fill_connected(const Stone board[][19], int row, int col, bool connected_part[][19], Stone player);
void fill_cell_liberties(const Stone board[][19], int row, int col, bool liberties[][19]);
void fill_liberties(const Stone board[][19], int row, int col, const bool connected_part[][19], bool liberties[][19]);

int check_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19]) {
	if (out_of_board(row, col)) {
		return -1;
	} else if (board[row][col] == Empty) {
		return -2;
	}

	Stone player = board[row][col];
	fill_connected(board, row, col, connected_part, player);
	fill_liberties(board, row, col, connected_part, liberties);

	int sumOfLiberties = 0;
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j)
			sumOfLiberties += liberties[i][j];
	}

	return sumOfLiberties;
}

void fill_connected(const Stone board[][19], int row, int col, bool connected_part[][19], Stone player) {
	if (in_board(row+1, col) && board[row+1][col] == player && !connected_part[row+1][col]) {
		connected_part[row+1][col] = true;
		fill_connected(board, row+1, col, connected_part, player);
	}

	if (in_board(row-1, col) && board[row-1][col] == player && !connected_part[row-1][col]) {
		connected_part[row-1][col] = true;
		fill_connected(board, row-1, col, connected_part, player);
	}

	if (in_board(row, col+1) && board[row][col+1] == player && !connected_part[row][col+1]) {
		connected_part[row][col+1] = true;
		fill_connected(board, row, col+1, connected_part, player);
	}

	if (in_board(row, col-1) && board[row][col-1] == player && !connected_part[row][col-1]) {
		connected_part[row][col-1] = true;
		fill_connected(board, row, col-1, connected_part, player);
	}

	return;
}

void fill_cell_liberties(const Stone board[][19], int row, int col, bool liberties[][19]) {
	if (in_board(row+1, col) && board[row+1][col] == Empty && !liberties[row+1][col]) {
		liberties[row+1][col] = true;
	}

	if (in_board(row-1, col) && board[row-1][col] == Empty && !liberties[row-1][col]) {
		liberties[row-1][col] = true;
	}

	if (in_board(row, col+1) && board[row][col+1] == Empty && !liberties[row][col+1]) {
		liberties[row][col+1] = true;
	}

	if (in_board(row, col-1) && board[row][col-1] == Empty && !liberties[row][col-1]) {
		liberties[row][col-1] = true;
	}
}

void fill_liberties(const Stone board[][19], int row, int col, const bool connected_part[][19], bool liberties[][19]) {

	fill_cell_liberties(board, row, col, liberties);

	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			if (connected_part[i][j]) {
				fill_cell_liberties(board, i, j, liberties);
			}
		}
	}
}

/***********************************************************************
 * TODO_2: Check whether a player has captured stones, and mark them.
 * 
 * - Check the whole game board for any captured stones of the selected 
 *   player. Set the corresponding elements in captured to be true. 
 *   Return true if and only if there are any captured stones.
 ***********************************************************************/

bool find_captured(const Stone board[][19], Stone player, bool captured[][19]) {
	bool connected_part[19][19], liberties[19][19];
	bool isCaptured = false;

	for (int row = 0; row < 19; ++row) {
		for (int col = 0; col < 19; ++col) {
			if (board[row][col] == player) {
				fill(&connected_part[0][0], &connected_part[18][18]+1, false);
				fill(&liberties[0][0], &liberties[18][18]+1, false);
				int numOfLiberties = check_liberties(board, row, col, connected_part, liberties);
				if (!numOfLiberties) {
					isCaptured = true;
					captured[row][col] = true;
				}
			}
		}
	}

	return isCaptured;
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

	if (board[row][col] != Empty) {
		return -2;
	}

	board[row][col] = player;

	bool captured[19][19];
	fill(&captured[0][0], &captured[18][18]+1, false);

	bool isSuicide = find_captured(board, player, captured);
	if (isSuicide) {
		board[row][col] = Empty;
		return -3;
	}

	fill(&captured[0][0], &captured[18][18]+1, false);

	Stone opponent = (player == White ? Black : White);
	bool isCaptured = find_captured(board, opponent, captured);
	if (isCaptured) {
		for (int i = 0; i < 19; ++i) {
			for (int j = 0; j < 19; ++j) {
				if (captured[i][j]) {
					board[i][j] = Empty;
				}
			}
		}
	}

	bool changedRecord = !(record[counter][0] == row && record[counter][1] == col);

	record[counter][0] = row;
	record[counter][1] = col;

	if (++counter > max_steps || changedRecord) {
		max_steps = counter;
	}

	return 0;
}

/***********************************************************************
 * TODO_4: Jump to the given step of the game.
 * 
 * - Set the board to the state at target step, and correctly set the 
 *   value of counter and max_steps.
 ***********************************************************************/

void jump_to(Stone board[][19], int target, int record[][2], int& counter, int& max_steps) {
	fill(&board[0][0], &board[18][18]+1, Empty);
	counter = 0;
	for (int i = 0; i < target; ++i) {
		Stone player = (i%2 == 0 ? Black : White);
		int row = record[i][0];
		int col = record[i][1];
		if (row == -1 && col == -1) {
			++counter;
		} else {
			edit(board, player, row, col, record, counter, max_steps);
		}
	}
}
