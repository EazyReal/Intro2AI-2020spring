#include "board.h"

//vector printing overload
template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << " ]";
    os << endl;
    return os;
}

board::board(VVI b, bool lastc) : b(b), lastc(lastc)
{
    rep(i, 0, BOARDSZ) rep(j, 0, BOARDSZ) b[i][j]--;
};

board::board()
{
    b = VVI(BOARDSZ, VI(BOARDSZ, -1));
    lastc = WHITE;
    //cout << b;
};

bool board::just_play_color()
{
    return lastc;
}

bool board::check(int pos, int color)
{
    DECODE(pos,x,y);
    if(b[x][y] != -1) return 0; //only empty can do
    // middle 6*6 
    if(x > 0 && x < 7 && y > 0 && y < 7) return 1;
    // 4 side
    else{

    }
    return 1;
}

void board::update()
{
    return;
}

bool board::no_move()
{
    return 1;
}

void board::add(int pos, int color)
{
    return;
}

int board::simulate(int c)
{
    return 1;
}