#ifndef BFS_H
#define BFS_H

#include "custom_header.hpp"

class BFS : public Solver
{
private:
    Board<pii> vis;
    int node_expanded;
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

pair<vector<pii>, int> BFS::solve(pii s, pii t)
{
    node_expanded = 0;
    vector<pii> path;
    queue<pii> q;
    q.push(s);
    vis[cor(s)] = s;
    while(!q.empty())
    {
        pii cur = q.front(); q.pop();
        node_expanded++;
        if(cur == t) break;
        for(auto &d : dxdy)
        {
            pii nxt = cur + d;
            if(!inrange(nxt) || vis[cor(nxt)] != pii(-1,-1)) continue;
            //if(nxt == t) 
            q.push(nxt);
            vis[cor(nxt)] = cur;
        }
    }
    pii cur = t;
    while(1)
    {
        if(vis[cor(cur)] == cur) { path.pb(cur); break;}
        path.pb(cur);
        cur = vis[cor(cur)];
    }
    reverse(path.begin(), path.end());
    return mp(path, node_expanded);
}

void BFS::init()
{
    vis = Board<pii>();
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), pii(-1, -1));
    cout << name << " solver initialized." << endl;
}


void BFS::print()
{
    cout << "bfs_structure_test\n";
}

#endif