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

class BFS : public Solver
{
private:
    Board vis;
public:
    //string name; this will cause the name be empty string
    BFS();
    pair<vector<pii>, int> solve(pii x, pii y);
    void init();
    void print();
};

BFS::BFS()
{
    name = "BFS";
}

pair<vector<pii>, int> BFS::solve(pii x, pii y)
{
    vector<pii> path;
    return mp(path, 0);
}

void BFS::init()
{
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), 0);
}


void BFS::print()
{
    cout << "bfs_structure_test\n";
}



signed main()
{
    cout << "Introduction to AI 2020 spring HW1 by yan-tong lin" << endl;
    cout << "solver type list" << endl;
    //list of solver names
    vector<Solver*> solvers;
    solvers.pb(new BFS());
    rep(i, 0, solvers.size()) cout << "id " << i << ":, algorithm :" << solvers[i]->name << endl; 
    cout << "input solver id:" << endl;
    int id; int sx, sy, tx, ty;
    cin >> id;
    solvers[id]->init();
    cout << "input start coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> sx >> sy;
    cout << "input start coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> tx >> ty;
    auto dat = solvers[id]->solve(mp(sx, sy), mp(tx, ty));
    vector<pii>& path = dat.X;
    int nodes_expanded = dat.Y;
    cout << "the past is listed as follow:\n";
    rep(i, 0, path.size()) cout <<  path[i] << endl;
    debug(nodes_expanded);

    return 0;
}