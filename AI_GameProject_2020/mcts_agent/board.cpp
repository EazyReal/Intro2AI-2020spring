#include "board.h"

//vector printing overload
template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) 
{
    //os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    //os << " ]";
    os << endl;
    return os;
}


inline bool inrange(int x, int y)
{
    return x >= 0 && x < BOARDSZ && y > 0 && y < BOARDSZ;
}

inline bool inner(int x, int y)
{
    return x > 0 && x < 7 && y > 0 && y < 7;
}

//convert TA API to my board info
// BLACK 0, WHITE 1, EMPTY -1, CORNER(NOGO) -2
board::board(VVI b, bool lastc) : b(b), lastc(lastc)
{
    trav(i,j) b[i][j]--;
};

//init with empty board and BLACK to go
board::board()
{
    b = VVI(BOARDSZ, VI(BOARDSZ, -1));
    lastc = WHITE;
    //cout << b;
};

// be sure lastc contain the desired value 
bool board::just_play_color()
{
    return lastc;
}

// check availability for action (pos, color)
bool board::check(int pos, int color)
{
    DECODE(pos,x,y);
    if(b[x][y] != EMPTY) return 0; //only empty can do
    // middle 6*6 
    if(inner(x,y)) return 1;
    // 4 side
    else{
        dxy(dx,dy)
        {
            int nx = x + dx;
            int ny = y + dy;
            bool flag1 = 0; //nxt stone on this direction is opposite color
            if(inrange(nx,ny) && b[nx][ny] == !color) flag1 = 1;
            bool flag2 = 0;
            //there is the same color on this direction(other then adject to x, and break if encounter -2, -1)
            while(inrange(nx+dx, ny+dy))
            {
                nx += dx;
                ny += dy;
                if(b[nx][ny] == color) {flag2 = 1; break;}
                if(b[nx][ny] < 0) break;
            }
            if(flag1 && flag2) return 1;
        }
    }
    return 1;
}

void board::update()
{
    return;
}

bool board::no_move()
{
    bool ok = 0;
    bool toplay = !lastc;
    trav(i,j) ok |= check(ID(i,j), toplay);
    return !ok;
}

void board::add(int pos, int color)
{
    assert(check(pos,color));
    DECODE(pos,x,y);
    b[x][y] = color;
    lastc = color;
    dxy(dx,dy)
    {
        int nx = x + dx;
        int ny = y + dy;
        bool flag1 = 0; //nxt stone on this direction is opposite color
        if(inrange(nx,ny) && b[nx][ny] == !color) flag1 = 1;
        bool flag2 = 0;
        //there is the same color on this direction(other then adject to x, and break if encounter -2, -1)
        while(inrange(nx+dx, ny+dy))
        {
            nx += dx;
            ny += dy;
            if(b[nx][ny] == color) {flag2 = 1; break;}
            if(b[nx][ny] < 0) break;
        }
        debug(flag1);
        debug(flag2);
        if(flag1 && flag2)
        {
            nx = x, ny = y;
            while(inrange(nx+dx, ny+dy))
            {
                nx += dx;
                ny += dy;
                if(b[nx][ny] == !color) b[nx][ny] = color; //flip
                if(b[nx][ny] < 0) break;
            }
        }
    }
    return;
}

int board::simulate(int c)
{
    return 1;
}

void board::print()
{
    //cout << b;
    rep(i, 0, BOARDSZ) cout << i << ' ';
    cout << endl;
    trav(i, j)
    {
        if(b[i][j] == -1) cout << '.';
        if(b[i][j] == 0) cout << 'o';
        if(b[i][j] == 1) cout << 'x';
        if(j==BOARDSZ-1 ) cout << ' ' << i;
        cout << (j==BOARDSZ-1 ? '\n' : ' ');
    }
    return;
}