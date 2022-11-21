#include <array>
#include <cstdlib> //rand()
#include <ctime>   //time()

using namespace std;

typedef struct {
    int term;
    int score;
    array<array<int, 4>, 4> state; // 4 X 4
} blockLog;

int create_random(blockLog *test);
int move_block_left(blockLog *test);
int move_block_right(blockLog *test);
int move_block_up(blockLog *test);
int move_block_down(blockLog *test);
bool is_possible_moving(int (*compare_arr)[4], int (*target_arr)[4]);
