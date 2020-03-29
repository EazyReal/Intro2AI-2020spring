#ifndef BFS_H
#define BFS_H

#include "custom_header.hpp"

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
    cout << name << " solver initialized." << endl;
}


void BFS::print()
{
    cout << "bfs_structure_test\n";
}

#endif