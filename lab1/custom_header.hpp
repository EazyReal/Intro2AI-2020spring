#ifndef CUSTOM_H
#define CUSTOM_H

#include <bits/stdc++.h>
using namespace std;

#define N 8

#define rep(i, s, t) for(int i = s, _t = (t); i < _t; i++)
#define pb push_back
#define debug(x) std::cout << #x << ": " << x << endl

template<class T>
using Board = array<array<T, 8>, 8>;

// S: start(hidden), T : end (hidden), D : calc delta by hidden, P print car, R : all wrapped
// C: end and calc by end
#define TIMER_S auto ___st_time = chrono::high_resolution_clock::now();
#define TIMER_T auto ___ed_time = chrono::high_resolution_clock::now();
#define TIMER_D(var) double var = chrono::duration_cast<chrono::nanoseconds>(___ed_time - ___st_time).count(); var *= 1e-9;
#define TIMER_C(var) TIMER_T TIMER_D(var)
#define TIMER_P(var) cout << "Time taken by the solver is :" << fixed << var << setprecision(9);  cout << " sec" << endl;
#define TIMER(xxx) TIMER_S xxx TIMER_T TIMER_D(_tt) TIMER_P(_tt)

#define pii pair<int, int>
#define X first
#define Y second
#define cor2(point) point.X, point.Y
#define cor(point) point.X][point.Y
#define mp make_pair
pii operator+(const pii&x, const pii&y) { return mp(x.X+y.X, x.Y+y.Y);}
pii operator-(const pii&x, const pii&y) { return mp(x.X-y.X, x.Y-y.Y);}

pii dxdy[8] = 
{
    {1,2},{-1,2},{1,-2},{-1,-2},
    {2,1},{-2,1},{2,-1},{-2,-1}
};

bool inrange(pii x)
{
    return (x.X>=0) && (x.Y>=0) && (x.X<N) && (x.Y<N);
}

std::ostream& operator<<(std::ostream& os, pii& p) //tested
{
    os << "("<<  p.first << ", " <<  p.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, vector<pii>& path) //tested
{
    rep(i, 0, path.size()) os <<  path[i] << " \n"[i==path.size()-1 || (i+1)%10==0];
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, Board<T>& b) //tested
{
    rep(i, 0, N)
    {
        rep(j, 0, N) os << b[i][j] << " ";
        os << endl;
    }
    return os;
}

class Solver
{
private:
public:
    string name;
    int node_expanded;
    Board<pii> vis;
    virtual pair<vector<pii>, int> solve(pii x, pii y, double TL=10.0) = 0;
    void init();
    void print();
    void construct_path(vector<pii> &path, pii t);
};

void Solver::construct_path(vector<pii> &path, pii t)
{
    pii cur = t;
    while(1)
    {
        if(vis[cor(cur)] == cur) { path.pb(cur); break;}
        path.pb(cur);
        cur = vis[cor(cur)];
    }
    reverse(path.begin(), path.end());
    return;
}

void Solver::init()
{
    vis = Board<pii>();
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), pii(-1, -1));
    //cout << name << " solver initialized." << endl;
}

void Solver::print()
{
    cout << "printing " <<   name << " board\n";
    cout << vis;
}


#endif