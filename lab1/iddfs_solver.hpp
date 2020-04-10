#ifndef IDDFS_H
#define IDDFS_H

#include "custom_header.hpp"

class IDDFS : public Solver
{
private:
public:
    //string name; this will cause the name be empty string
    IDDFS();
    bool dfs(int d, pii s, pii p, pii t, int maxd);
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

IDDFS::IDDFS()
{
    name = "IDDFS";
}

bool IDDFS::dfs(int d, pii s, pii p, pii t, int maxd)
{
    if(d > maxd) return false; //dont set vis v=before this!!!!, debug by assert(len(path) = maxd+1)
    node_expanded++; //after d>maxd 441, before=> 2134, when 2, 0, 0, 0, 7 input
    cur_node_expanded++;
    max_node_expanded = max(max_node_expanded, cur_node_expanded);
    bool ret = false;
    vis[cor(s)] = p;
    if(s == t) return true;
    //else if(d > maxd) return false; this might cause assertion failed(for the node is expanded at maxd+1)
    //different return condition cause slightly difference in node_expanded
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        if(!inrange(nxt)||vis[cor(nxt)] != pii(-1,-1)) continue; //typo, continue to break
        //if(!inrange(nxt)) break;
        if(d+1 <= maxd) ret |= dfs(d+1, nxt, s, t, maxd); //constrain here is ok, too, or use minus to zero
        if(ret) break; //this may reduce node expanded
    }
    cur_node_expanded--;
    if(!ret) vis[cor(s)] = pii(-1,-1); //if not done, revover vis
    return ret;
}

pair<vector<pii>, int> IDDFS::solve(pii s, pii t, double TL)
{
    TIMER(
    node_expanded = 0;
    max_node_expanded = 0;
    cur_node_expanded = 0;
    int maxd = 0;
    while(!dfs(0, s, s, t, maxd) && maxd <= 1000)
    {
        Solver::init();
        ++maxd;
        debug(maxd);
        TIMER_C(checker)
        if(checker > TL)
        {
            cout << "TLE break at " << TL <<  " seconds";
            break;
        }
    }
    )
    //print();
    vector<pii> path;
    construct_path(path, t);
    //debug(path); debug(maxd);
    assert(path.size() == maxd+1); // s -d++- 1 - 2 - 3 - d++ t 
    return mp(path, node_expanded);
}

#endif