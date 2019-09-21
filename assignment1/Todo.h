#ifndef TODO_H
#define TODO_H

enum Stone {Empty=0, Black=1, White=2};

int check_liberties(const Stone board[][19], int row, int col, bool connected_part[][19], bool liberties[][19]);
bool find_captured(const Stone board[][19], Stone player, bool captured[][19]);
int edit(Stone board[][19], Stone player, int row, int col, int record[][2], int& counter, int& max_steps);
void jump_to(Stone board[][19], int target, int record[][2], int& counter, int& max_steps);

#endif /* TODO_H */