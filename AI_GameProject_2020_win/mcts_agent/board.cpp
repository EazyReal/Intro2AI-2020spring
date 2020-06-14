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
    return x >= 0 && x < BOARDSZ && y >= 0 && y < BOARDSZ;
}

inline bool inner(int x, int y)
{
    return x > 0 && x < BOARDSZ-1 && y > 0 && y < BOARDSZ-1;
}

//convert TA API to my board info
// BLACK 0, WHITE 1, EMPTY -1, CORNER(NOGO) -2
board::board(VVI b, bool lastc) : lastc(lastc)
{
    this->b = b;
    trav(i,j) this->b[i][j]--;
};

//init with empty board and BLACK to go
board::board()
{
    b = VVI(BOARDSZ, VI(BOARDSZ, -1));
    b[0][0] = b[0][BOARDSZ-1] = b[BOARDSZ-1][BOARDSZ-1] = b[BOARDSZ-1][0] = -2; //bug
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
    assert(color == !lastc);
    if(b[x][y] != EMPTY) { return 0;} //only empty can do, corner is exluded in this step
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
    return 0;
}

/*
void board::update()
{
    return;
}*/

vector<int> board::all_moves()
{
    VI ret;
    bool toplay = !lastc;
    trav(i,j)if(check(ID(i,j), toplay))
    {
        ret.push_back(ID(i,j));
    }
    return ret;
}

bool board::no_move()
{
    return all_moves().size() == 0;
}

// note that pass is with pos PASS(-1)
void board::add(int pos, int color)
{
    if(pos == PASS)
    {
        assert(!lastc == bool(color));
        lastc = !lastc;
        return;
    }

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
        if(flag1 && flag2)
        {
            nx = x, ny = y;
            while(inrange(nx+dx, ny+dy))
            {
                nx += dx;
                ny += dy;
                if(b[nx][ny] == !color) b[nx][ny] = color; //flip
                else if(b[nx][ny] < 0 || b[nx][ny] == color) break; //bug, else
            }
        }
    }
    return;
}


int board::status()
{
    // calc territory
    int w = 0, bl = 0, e = 0;
    trav(i, j)
    {
        if(b[i][j] == WHITE) w++;
        if(b[i][j] == BLACK) bl++;
        //if(b[i][j] == EMPTY) e++; return NOTEND; can have empty when end
    }
    return (w > bl ? WHITE : BLACK); //NO IMPLEMENT TIE
}


int board::simulate(int c)
{
    int pass_cnt = 0;
    //int toplay = c;
    //toplay = !just_play_color();
    assert(c == !lastc);
    while(1)
    {
        //print();
        VI moves = all_moves();
        //cout << moves  << endl;
        int n = moves.size();
        if(n == 0 )
        {
            pass_cnt++;
            add(-1, !lastc);
            if(pass_cnt == 2) return status(); 
            else continue;
        }
        add(moves[rand()%n], !lastc);
        pass_cnt = 0;
    }
    assert(0);
    return PASS;
}

void board::print()
{
    //cout << b;
    rep(i, 0, BOARDSZ) cout << i << ' ';
    cout << endl;
    trav(i, j)
    {
        if(b[i][j] < 0) cout << '.';
        if(b[i][j] == 0) cout << 'o';
        if(b[i][j] == 1) cout << 'x';
        if(j==BOARDSZ-1 ) cout << ' ' << i;
        cout << (j==BOARDSZ-1 ? '\n' : ' ');
    }
    return;
}