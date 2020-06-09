#ifndef BOARDH
#define BOARDH

// dependencys
#include <bits/stdc++.h>
using namespace std;

// hyper param about board
#define BOARDSZ 8
#define BOARDVL 64
#define BLACK 0
#define WHITE 1

// notations
#define VVI vector<vector<int>>

class board
{
public:
    VVI b;
    bool just_play_color();
    bool check(int pos, int color); //check validity of action
    void add(int pos, int color);
    int simulate(int color);
    //double get_v();s
    board(VVI b);
    board();

private:
};

#endif //BOARDH