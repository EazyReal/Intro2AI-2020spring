#ifndef IDDFS_H
#define IDDFS_H

#include "custom_header.hpp"

class IDDFS : public Solver
{
private:
    Board<pii> vis;
    int node_expanded;
public:
    //string name; this will cause the name be empty string
    IDDFS();
    bool dfs(int d, pii s, pii p, pii t, int maxd);
    pair<vector<pii>, int> solve(pii x, pii y);
    void init();
    void print();
};

IDDFS::IDDFS()
{
    name = "IDDFS";
}

bool IDDFS::dfs(int d, pii s, pii p, pii t, int maxd)
{
    node_expanded++;
    bool ret = false;
    vis[cor(s)] = p;
    if(d > maxd) return false;
    if(s == t) return true;
    //else if(d > maxd) return false; this might cause assertion failed(for the node is expanded at maxd+1)
    //different return condition cause slightly difference in node_expanded
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        if(!inrange(nxt)||vis[cor(nxt)] != pii(-1,-1)) continue; //typo, continue to break
        ret |= dfs(d+1, nxt, s, t, maxd);
        if(ret) break; //this may reduce node expanded
    }
    if(!ret) vis[cor(s)] = pii(-1,-1);
    return ret;
}

pair<vector<pii>, int> IDDFS::solve(pii s, pii t)
{
    node_expanded = 0;
    int maxd = 0;
    while(!dfs(0, s, s, t, maxd) && maxd <= 1000)
    {
        init();
        ++maxd;
        debug(maxd);
        debug(node_expanded);
    }
    pii cur = t;
    vector<pii> path;
    while(1)
    {
        path.pb(cur);
        cur = vis[cor(cur)];
        if(vis[cor(cur)] == cur)
        {
            path.pb(cur);
            break;
        }
    }
    reverse(path.begin(), path.end());
    assert(path.size() == maxd+1); // s -d++- 1 - 2 - 3 - d++ t 
    return mp(path, node_expanded);
}

void IDDFS::init()
{
    vis = Board<pii>();
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), pii(-1, -1));
    //cout << name << " solver initialized." << endl;
}


void IDDFS::print()
{
    cout << "IDDFS_structure_test\n";
}

#endif