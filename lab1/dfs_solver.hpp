#ifndef DFS_H
#define DFS_H

#include "custom_header.hpp"

class DFS : public Solver
{
private:
    Board vis;
public:
    //string name; this will cause the name be empty string
    DFS();
    pair<vector<pii>, int> solve(pii x, pii y);
    void init();
    void print();
};

DFS::DFS()
{
    name = "DFS";
}

pair<vector<pii>, int> DFS::solve(pii x, pii y)
{
    vector<pii> path;
    return mp(path, 0);
}

void DFS::init()
{
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), 0);
    cout << name << " solver initialized." << endl;
}


void DFS::print()
{
    cout << "DFS_structure_test\n";
}

#endif