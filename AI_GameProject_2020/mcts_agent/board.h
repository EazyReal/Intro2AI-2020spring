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
#define EMPTY -1
#define CORNER -2

#define NOTEND -1
//position save for pass
#define PASS -1

// notations
#define VI vector<int>
#define VVI vector<vector<int>>
#define VD vector<double>

// syntax sugar
#define rep(i, s, t) for(int i = s; i < t; ++i)
#define trav(i,j) rep(i,0,BOARDSZ)rep(j,0,BOARDSZ)
#define dxy(dx,dy) rep(dx,-1,2)rep(dy,-1,2)if(dx != 0 || dy != 0)
#define DECODE(pos,x,y) int x = pos/BOARDSZ; int y = pos%BOARDSZ
#define ID(x,y) (x*BOARDSZ+y)
#define XY(pos) pos/BOARDSZ, pos%BOARDSZ
#define debug(x) cerr << #x << ": "  << x << endl

//const vector<pair<int,int>> dxdy8 = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};

class board
{
public:
    VVI b;
    // 0, black, 1 white, -1 not claimed, -2 coner;
    bool lastc;

    bool just_play_color(); //be sure to get the right color
    bool check(int pos, int color); //check validity of action
    bool no_move();
    VI all_moves();
    void add(int pos, int color);
    int simulate(int color);
    int status(); //update information
    void print();

    //constructors
    board(VVI b, bool lastc); 
    board();

private:
};

#endif //BOARDH