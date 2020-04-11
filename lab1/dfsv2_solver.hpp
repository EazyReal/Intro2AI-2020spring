#ifndef DFS2_H
#define DFS2_H

#include "custom_header.hpp"

class DFS2 : public Solver
{
private:
public:
    //string name; this will cause the name be empty string
    DFS2();
    bool dfs2(int d, pii s, pii t);
    vector<pii> path;
    vector<vector<int>> dep; //relaxtion based
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

DFS2::DFS2()
{
    name = "DFS2_v2";
}

bool DFS2::dfs2(int d, pii s, pii t) //s = current, p = from, d = current depth, t =  
{
    bool ret = false;
    if(s == t) return true;
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        //nxt is not in range or no relexation, init d = INF, so if no visit will explore
        if(!inrange(nxt)||dep[cor(nxt)] <= d+1) continue;
        path.pb(nxt);
        node_expanded++;
        cur_node_expanded++;
        max_node_expanded = max(max_node_expanded, cur_node_expanded);
        dep[cor(nxt)] = d+1;
        ret |= dfs2(d+1, nxt, t);
        if(ret) break; //success, no pop_back this path
        path.pop_back();
        cur_node_expanded--;
    }
    return ret;
}

pair<vector<pii>, int> DFS2::solve(pii s, pii t, double TL)
{
    node_expanded = 0;
    max_node_expanded = 0;
    cur_node_expanded = 0;
    path.clear();
    int INF = N*N + N;
    dep = vector<vector<int>>(N, vector<int>(N, INF));
    //init();
    //start dfs
    node_expanded++;
    cur_node_expanded++;
    max_node_expanded = max(max_node_expanded, cur_node_expanded);
    dep[cor(s)] = 0;
    path.pb(s);
    dfs2(0, s, t);
    return mp(path, node_expanded);
}
#endif