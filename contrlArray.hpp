#include <array>
#include <cstdlib> //rand()
#include <ctime>   //time()

using namespace std;

typedef struct {
    int term;
    array<array<int, 4>, 4> state; // 4 X 4
} blockLog;

int create_random(blockLog *test);
void move_block_left(blockLog *test);
void move_block_right(blockLog *test);
void move_block_up(blockLog *test);
void move_block_down(blockLog *test);
