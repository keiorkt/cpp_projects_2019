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

int check_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19]) {
	return -1;
}

/***********************************************************************
 * TODO_2: Check whether a player has captured stones, and mark them.
 * 
 * - Check the whole game board for any captured stones of the selected 
 *   player. Set the corresponding elements in captured to be true. 
 *   Return true if and only if there are any captured stones.
 ***********************************************************************/

bool find_captured(const Stone board[][19], Stone player, bool captured[][19]) {
	return false;
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
	return -1;
}

/***********************************************************************
 * TODO_4: Jump to the given step of the game.
 * 
 * - Set the board to the state at target step, and correctly set the 
 *   value of counter and max_steps.
 ***********************************************************************/

void jump_to(Stone board[][19], int target, int record[][2], int& counter, int& max_steps) {
	
}