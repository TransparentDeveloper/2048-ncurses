#include "contrlArray.hpp"

bool is_possible_moving(int (*compare_arr)[4], int (*target_arr)[4]) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (compare_arr[row][col] != target_arr[row][col])
                return true;
        }
    }
    return false;
}

void move_block_left(blockLog *test) {
    int new_col = 0;
    int stop_point = 0;

    for (int row = 0; row < 4; row++) {
        stop_point = 0;

        for (int col = 0; col < 4; col++) {
            new_col = col;
            while (new_col > 0 && new_col < 4) {
                if (((test->state).at(row)).at(new_col) == 0 ||
                    new_col <= stop_point) {
                    break;
                }
                // if the value on the left is 0
                if (((test->state).at(row)).at(new_col - 1) == 0) {
                    ((test->state).at(row)).at(new_col - 1) =
                        ((test->state).at(row)).at(new_col);
                    ((test->state).at(row)).at(new_col) = 0;
                    new_col--;
                }
                // if the value on the left is equal to its value
                else if (((test->state).at(row)).at(new_col - 1) ==
                         ((test->state).at(row)).at(new_col)) {
                    ((test->state).at(row)).at(new_col - 1) *= 2;
                    ((test->state).at(row)).at(new_col) = 0;
                    new_col--;

                    // Update stop_point
                    stop_point = new_col;
                }
                // if the value on the left is not 0 and is different from
                // itself
                else {
                    break;
                }
            }
        }
    }
}
void move_block_right(blockLog *test) {
    int new_col = 0;
    int stop_point = 4 - 1;

    for (int row = 0; row < 4; row++) {
        stop_point = 4 - 1;

        for (int col = 4 - 1; col >= 0; col--) {
            new_col = col;
            while (new_col >= 0 && new_col < 4 - 1) {
                if (((test->state).at(row)).at(new_col) == 0 ||
                    new_col >= stop_point) {
                    break;
                }
                // if the value on the right is 0
                if (((test->state).at(row)).at(new_col + 1) == 0) {
                    ((test->state).at(row)).at(new_col + 1) =
                        ((test->state).at(row)).at(new_col);
                    ((test->state).at(row)).at(new_col) = 0;
                    new_col++;
                }
                // if the value on the right is equal to its value
                else if (((test->state).at(row)).at(new_col + 1) ==
                         ((test->state).at(row)).at(new_col)) {
                    ((test->state).at(row)).at(new_col + 1) *= 2;
                    ((test->state).at(row)).at(new_col) = 0;
                    new_col++;
                    stop_point = new_col;
                }
                // if the value on the right is not 0 and is different from
                // itself
                else {
                    break;
                }
            }
        }
    }
}
void move_block_up(blockLog *test) {
    int new_row = 0;
    int stop_point = 0;

    for (int col = 0; col < 4; col++) {
        stop_point = 0;

        for (int row = 0; row < 4; row++) {
            new_row = row;
            while (new_row > 0 && new_row < 4) {
                // if the value of the cureent block is 0
                if (((test->state).at(new_row)).at(col) == 0 ||
                    new_row <= stop_point) {
                    break;
                }
                // if the value above is 0
                if (((test->state).at(new_row - 1)).at(col) == 0) {
                    ((test->state).at(new_row - 1)).at(col) =
                        ((test->state).at(new_row)).at(col);
                    ((test->state).at(new_row)).at(col) = 0;
                    new_row--;
                }
                // if the value above is equal to its value
                else if (((test->state).at(new_row - 1)).at(col) ==
                         ((test->state).at(new_row)).at(col)) {
                    ((test->state).at(new_row - 1)).at(col) *= 2;
                    ((test->state).at(new_row)).at(col) = 0;
                    new_row--;
                    stop_point = new_row;
                }
                // if the value above is not 0 and is different from itself
                else {
                    break;
                }
            }
        }
    }
}
void move_block_down(blockLog *test) {
    int new_row = 0;
    int stop_point = 4 - 1;
    for (int col = 0; col < 4; col++) {
        stop_point = 4 - 1;

        for (int row = 4 - 1; row >= 0; row--) {
            new_row = row;
            while (new_row >= 0 && new_row < 4 - 1) {
                // if the value of the current block is 0
                if (((test->state).at(new_row)).at(col) == 0 ||
                    new_row >= stop_point) {
                    break;
                }
                // if the value below is 0
                if (((test->state).at(new_row + 1)).at(col) == 0) {
                    ((test->state).at(new_row + 1)).at(col) =
                        ((test->state).at(new_row)).at(col);
                    ((test->state).at(new_row)).at(col) = 0;
                    new_row++;
                }
                // if the value below is equal to its value
                else if (((test->state).at(new_row + 1)).at(col) ==
                         ((test->state).at(new_row)).at(col)) {
                    ((test->state).at(new_row + 1)).at(col) *= 2;
                    ((test->state).at(new_row)).at(col) = 0;
                    new_row++;
                    stop_point = new_row;
                }
                // if the value above is not 0 and is different from itself
                else {
                    break;
                }
            }
        }
    }
}

bool check_vaild(blockLog *test) {
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            if (((test->state).at(row)).at(col) == 0)
                return true;

    return false;
}

int create_random(blockLog *test) {
    if (!check_vaild(&(*test))) {
        return -1;
    }
    srand((unsigned int)time(NULL)); // seed

    int random_x, random_y;
    random_x = random_y = 0;
    bool invalid = true;

    while (invalid) {
        random_x = rand() % 4;
        random_y = rand() % 4;

        if (((test->state).at(random_y)).at(random_x) == 0)
            invalid = false;
    }

    ((test->state).at(random_y)).at(random_x) = 2;
    return 1;
}
