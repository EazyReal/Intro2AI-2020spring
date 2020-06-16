#ifndef BOARDH
#define BOARDH

#define USE_HEURISTIC 
#define MIN_MAX
// min max sart when move is less than?
#define MIN_MAX_THRESHOULD 3

// dependencys
#include <bits/stdc++.h>
using namespace std;

// hyper param about board
#define BOARDSZ 8
#define BOARDVL 64

#define BLACK 0
#define WHITE 1
#define TIE -1

#define EMPTY -1
#define CORNER -2


//heuristic values
#define H_EDGE 3
#define H_INSIDE 2
#define H_NEDGE 1

#ifdef USE_HEURISTIC
constexpr array<array<int, BOARDSZ>, BOARDSZ> H = {{
    {H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE},
    {H_EDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE, H_EDGE},
    {H_EDGE,H_NEDGE,H_INSIDE,H_INSIDE,H_INSIDE,H_INSIDE,H_NEDGE, H_EDGE},
    {H_EDGE,H_NEDGE,H_INSIDE,H_INSIDE,H_INSIDE,H_INSIDE,H_NEDGE, H_EDGE},
    {H_EDGE,H_NEDGE,H_INSIDE,H_INSIDE,H_INSIDE,H_INSIDE,H_NEDGE, H_EDGE},
    {H_EDGE,H_NEDGE,H_INSIDE,H_INSIDE,H_INSIDE,H_INSIDE,H_NEDGE, H_EDGE},
    {H_EDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE,H_NEDGE, H_EDGE},
    {H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE,H_EDGE},
}};
#endif

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
    int empty_cnt();
    void add(int pos, int color);
    //void undo(int pos, int color);
    int simulate(int color, int pass_cnt = 0); //recursive mode
    //int min_max(int color, int pass_cnt = 0);
    int status(); //update information
    void print();

    //constructors
    board(VVI b, bool lastc); 
    board();

private:
};

int min_max(board cur_b, int color, int pass_cnt=0);
pair<int,int> min_max_agent(board cur_b, int color, int pass_cnt=0);

#endif //BOARDH