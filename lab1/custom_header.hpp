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

class Solver
{
private:
public:
    string name;
    virtual pair<vector<pii>, int> solve(pii x, pii y) = 0;
    virtual void init() = 0;
    virtual void print() = 0;
};

#endif