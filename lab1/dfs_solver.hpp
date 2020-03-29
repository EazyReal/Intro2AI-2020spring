#ifndef DFS_H
#define DFS_H

#include "custom_header.hpp"

class DFS : public Solver
{
private:
    Board<pii> vis;
    int node_expanded;
public:
    //string name; this will cause the name be empty string
    DFS();
    bool dfs(int d, pii s, pii p, pii t);
    pair<vector<pii>, int> solve(pii x, pii y);
    void init();
    void print();
};

DFS::DFS()
{
    name = "DFS";
}

bool DFS::dfs(int d, pii s, pii p, pii t)
{
    bool ret = false;
    node_expanded++;
    vis[cor(s)] = p;
    if(s == t) return true;
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        if(!inrange(nxt)||vis[cor(nxt)] != pii(-1,-1)) continue; //typo, continue to break
        ret |= dfs(d+1, nxt, s, t);
        if(ret) break;
    }
    if(!ret) vis[cor(s)] = pii(-1,-1);
    return ret;
}

pair<vector<pii>, int> DFS::solve(pii s, pii t)
{
    node_expanded = 0;
    vector<pii> path;
    init();
    dfs(0, s, s, t);
    pii cur = t;
    while(1)
    {
        path.pb(cur);
        //validity of path checking
        bool flag = (cur == vis[cor(cur)]);
        for(auto &di : dxdy) flag |= cur + di == vis[cor(cur)];
        assert(flag);

        cur = vis[cor(cur)];
        if(vis[cor(cur)] == cur)
        {
            path.pb(cur);
            break;
        }
    }
    reverse(path.begin(), path.end());
    return mp(path, node_expanded);
}

void DFS::init()
{
    vis = Board<pii>();
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), pii(-1, -1));
    //cout << name << " solver initialized." << endl;
}


void DFS::print()
{
    cout << "DFS_structure_test\n";
}

#endif