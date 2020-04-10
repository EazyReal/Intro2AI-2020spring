#ifndef BFS_H
#define BFS_H

#include "custom_header.hpp"

class BFS : public Solver
{
public:
    //string name; this will cause the name be empty string
    BFS();
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

BFS::BFS()
{
    name = "BFS";
}

pair<vector<pii>, int> BFS::solve(pii s, pii t, double TL)
{
    TIMER(
    node_expanded = 0;
    cur_node_expanded = 0;
    max_node_expanded = 0;
    vector<pii> path;
    queue<pii> q;
    node_expanded++;
    cur_node_expanded++;
    q.push(s);
    vis[cor(s)] = s;
    while(!q.empty())
    {
        cur_node_expanded--;
        pii cur = q.front(); q.pop();
        if(cur == t) break;
        for(auto &di : dxdy)
        {
            pii nxt = cur + di;
            if(!inrange(nxt) || vis[cor(nxt)] != pii(-1,-1)) continue;
            //if(nxt == t) 
            node_expanded++;
            cur_node_expanded++;
            max_node_expanded = max(max_node_expanded, cur_node_expanded);
            q.push(nxt);
            vis[cor(nxt)] = cur;
        }
    }
    )
    //print();
    Solver::construct_path(path, t);

    return mp(path, node_expanded);
}

#endif