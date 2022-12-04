#ifndef __CONTROLARRAY_H__
#define __CONTROLARRAY_H__

class ControlArray {
  public:
    ControlArray();
    ~ControlArray();

    int get_term();
    int get_score();
    int at(int y, int x);

    void increase_term();
    void decrease_term();

    void set_term(int term);
    void set_score(int score);
    void set_arr2d_compoent(int y, int x, int num);

    bool check_isZero();
    int create_random();

    void move_block_left();
    void move_block_right();
    void move_block_up();
    void move_block_down();

    bool is_possible_moving(int (*compare_arr)[4], int (*target_arr)[4]);

  private:
    int term;
    int score;
    int **arr2d;
};

#endif
