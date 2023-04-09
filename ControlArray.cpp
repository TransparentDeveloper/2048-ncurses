#include "ControlArray.hpp"
#include <cstdlib> //rand()
#include <ctime>   //time()

ControlArray::ControlArray() {
    this->term = 1;
    score = 0;
    arr2d = new int *[4];

    for (int row = 0; row < 4; row++) {
        arr2d[row] = new int[4];
    }

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            arr2d[row][col] = 0;
        }
    }
}

ControlArray::~ControlArray() { delete arr2d; }

int ControlArray::get_term() { return term; }
int ControlArray::get_score() { return score; }

int ControlArray::at(int y, int x) { return this->arr2d[y][x]; }

void ControlArray::set_term(int term) { this->term = term; }
void ControlArray::set_score(int score) { this->score = score; }

void ControlArray::increase_term() { (this->term)++; }
void ControlArray::decrease_term() { (this->term)--; }
void ControlArray::set_arr2d_compoent(int y, int x, int num) {
    this->arr2d[y][x] = num;
}

bool ControlArray::check_isZero() {
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            if (arr2d[row][col] == 0)
                return true;

    return false;
}

int ControlArray::create_random() {
    if (!check_isZero()) {
        return -1;
    }
    srand((unsigned int)time(NULL)); // seed

    int random_x, random_y;
    random_x = random_y = 0;
    bool invalid = true;

    while (invalid) {
        random_x = rand() % 4;
        random_y = rand() % 4;

        if (arr2d[random_y][random_x] == 0)
            invalid = false;
    }

    arr2d[random_y][random_x] = 2;
    return 1;
};

void ControlArray::move_block_left() {
    int new_col = 0;
    int stop_point = 0;

    for (int row = 0; row < 4; row++) {
        stop_point = 0;

        for (int col = 0; col < 4; col++) {
            new_col = col;
            while (new_col > 0 && new_col < 4) {
                if (arr2d[row][new_col] == 0 || new_col <= stop_point) {
                    break;
                }
                // if the value on the left is 0
                if (arr2d[row][new_col - 1] == 0) {
                    arr2d[row][new_col - 1] = arr2d[row][new_col];
                    arr2d[row][new_col] = 0;
                    new_col--;
                }
                // if the value on the left is equal to its value
                else if (arr2d[row][new_col - 1] == arr2d[row][new_col]) {
                    arr2d[row][new_col - 1] *= 2;
                    arr2d[row][new_col] = 0;
                    new_col--;

                    // Add score
                    (this->score) += arr2d[row][new_col];

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

void ControlArray::move_block_right() {
    int new_col = 0;
    int stop_point = 4 - 1;

    for (int row = 0; row < 4; row++) {
        stop_point = 4 - 1;

        for (int col = 4 - 1; col >= 0; col--) {
            new_col = col;
            while (new_col >= 0 && new_col < 4 - 1) {
                if (arr2d[row][new_col] == 0 || new_col >= stop_point) {
                    break;
                }
                // if the value on the right is 0
                if (arr2d[row][new_col + 1] == 0) {
                    arr2d[row][new_col + 1] = arr2d[row][new_col];
                    arr2d[row][new_col] = 0;
                    new_col++;
                }
                // if the value on the right is equal to its value
                else if (arr2d[row][new_col + 1] == arr2d[row][new_col]) {
                    arr2d[row][new_col + 1] *= 2;
                    arr2d[row][new_col] = 0;
                    new_col++;

                    // Add score
                    (this->score) += arr2d[row][new_col];

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
void ControlArray::move_block_up() {
    int new_row = 0;
    int stop_point = 0;

    for (int col = 0; col < 4; col++) {
        stop_point = 0;

        for (int row = 0; row < 4; row++) {
            new_row = row;
            while (new_row > 0 && new_row < 4) {
                // if the value of the cureent block is 0
                if (arr2d[new_row][col] == 0 || new_row <= stop_point) {
                    break;
                }
                // if the value above is 0
                if (arr2d[new_row - 1][col] == 0) {
                    arr2d[new_row - 1][col] = arr2d[new_row][col];
                    arr2d[new_row][col] = 0;
                    new_row--;
                }
                // if the value above is equal to its value
                else if (arr2d[new_row - 1][col] == arr2d[new_row][col]) {
                    arr2d[new_row - 1][col] *= 2;
                    arr2d[new_row][col] = 0;
                    new_row--;

                    // Add score
                    (this->score) += arr2d[new_row][col];

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
void ControlArray::move_block_down() {
    int new_row = 0;
    int stop_point = 4 - 1;

    for (int col = 0; col < 4; col++) {
        stop_point = 4 - 1;

        for (int row = 4 - 1; row >= 0; row--) {
            new_row = row;
            while (new_row >= 0 && new_row < 4 - 1) {
                // if the value of the current block is 0
                if (arr2d[new_row][col] == 0 || new_row >= stop_point) {
                    break;
                }
                // if the value below is 0
                if (arr2d[new_row + 1][col] == 0) {
                    arr2d[new_row + 1][col] = arr2d[new_row][col];
                    arr2d[new_row][col] = 0;
                    new_row++;
                }
                // if the value below is equal to its value
                else if (arr2d[new_row + 1][col] == arr2d[new_row][col]) {
                    arr2d[new_row + 1][col] *= 2;
                    arr2d[new_row][col] = 0;
                    new_row++;

                    // Add score
                    (this->score) += arr2d[new_row][col];

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

bool ControlArray::is_possible_moving(int (*compare_arr)[4],
                                      int (*target_arr)[4]) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (compare_arr[row][col] != target_arr[row][col])
                return true;
        }
    }
    return false;
}
