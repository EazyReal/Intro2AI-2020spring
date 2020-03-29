#ifndef CUSTOM_H
#define CUSTOM_H

#include <bits/stdc++.h>
using namespace std;

#define N 8

#define rep(i, s, t) for(int i = s, _t = (t); i < _t; i++)
#define pb push_back
#define debug(x) std::cout << #x << ": " << x << endl

typedef array<array<int, 8>, 8> Board;
#define pii pair<int, int>
#define X first
#define Y second
#define mp make_pair
pii operator+(const pii&x, const pii&y) { return mp(x.X+y.X, x.Y+y.Y);}
pii operator-(const pii&x, const pii&y) { return mp(x.X-y.X, x.Y-y.Y);}

std::ostream& operator<<(std::ostream& os, pii& p) //tested
{
    os << p.first << " " <<  p.second;
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