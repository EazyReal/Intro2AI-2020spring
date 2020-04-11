#ifndef IDDFS2_H
#define IDDFS2_H

#include "custom_header.hpp"

class IDDFS2 : public Solver
{
private:
public:
    vector<pii> path;
    vector<vector<int>> dep; //relaxtion based
    //string name; this will cause the name be empty string
    IDDFS2();
    bool dfs2(int d, pii s, pii t, int maxd);
    void init_dfs();
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

IDDFS2::IDDFS2()
{
    name = "IDDFS2";
}

bool IDDFS2::dfs2(int d, pii s, pii t, int maxd) //s = current, p = from, d = current depth, t =  
{
    bool ret = false;
    if(d > maxd) return false;
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
        ret |= dfs2(d+1, nxt, t, maxd);
        if(ret) break; //success, no pop_back this path
        path.pop_back();
        cur_node_expanded--;
    }
    return ret;
}

void IDDFS2::init_dfs()
{
    path.clear();
    int INF = N*N + N;
    dep = vector<vector<int>>(N, vector<int>(N, INF));
}


pair<vector<pii>, int> IDDFS2::solve(pii s, pii t, double TL)
{
    node_expanded = 0;
    max_node_expanded = 0;
    cur_node_expanded = 0;
    int maxd = 0;
    init_dfs();
    path.pb(s);
    node_expanded++;
    cur_node_expanded++;
    max_node_expanded = max(max_node_expanded, cur_node_expanded);
    dep[cor(s)] = 0;
    while(!dfs2(0, s, t, maxd) && maxd <= 100000)
    {
        init_dfs();
        dep[cor(s)] = 0;
        path.pb(s);
        maxd++;
    }
    //assert(path.size() == maxd+1); // s -d++- 1 - 2 - 3 - d++ t 
    return mp(path, node_expanded);
}

#endif