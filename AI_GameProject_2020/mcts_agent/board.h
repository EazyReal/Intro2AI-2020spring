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

//#define pos.x (pos%BOARDSZ)
//#define pos.y (pos%BOARDSZ)

// notations
#define VI vector<int>
#define VVI vector<vector<int>>
#define VD vector<double>

// syntax sugar
#define rep(i, s, t) for(int i = s; i < t; ++i)
#define DECODE(pos,x,y) int x = pos/BOARDSZ; int y = pos%BOARDSZ

class board
{
public:
    VVI b;
    // 0, black, 1 white, -1 not claimed, -2 coner;
    bool lastc;

    bool just_play_color(); //be sure to get the right color
    bool check(int pos, int color); //check validity of action
    bool no_move();
    void add(int pos, int color);
    int simulate(int color);
    void update(); //update information

    //constructors
    board(VVI b, bool lastc); 
    board();

private:
};

#endif //BOARDH