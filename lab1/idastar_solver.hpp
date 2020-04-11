#ifndef IDA_H
#define IDA_H

#include "custom_header.hpp"

class IDA : public Solver
{
private:
    std::function<int(const pii&, const pii&)> h;
public:
    //string name; this will cause the name be empty string
    IDA();
    int dfs(int d, pii s, pii p, pii t, int maxd);
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

IDA::IDA()
{
    h = [&](const pii &s, const pii &t){
        return manhattan_distance(s, t)/3;
    };
    name = "IDA";
}

//return value meaning, -1 found, INF not found any better, inbetween : the minimal nxt threshould for maxd;
int IDA::dfs(int d, pii s, pii p, pii t, int maxd)
{
    if(d > maxd) return d;//dont set vis v=before this!!!!, debug by assert(len(path) = maxd+1) 
    node_expanded++; //after d>maxd 441, before=> 2134, when 2, 0, 0, 0, 7 input
    cur_node_expanded++;
    max_node_expanded = max(max_node_expanded, cur_node_expanded);
    int ret = INT_MAX;
    vis[cor(s)] = p;
    if(s == t) return -1;
    //else if(d > maxd) return false; this might cause assertion failed(for the node is expanded at maxd+1)
    //different return condition cause slightly difference in node_expanded
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        if(!inrange(nxt)||vis[cor(nxt)] != pii(-1,-1)) continue; //typo, continue to break
        int nxtd = d + 1 - h(s,t) + h(nxt,t); //nxt heuristic
        //if(!inrange(nxt)) break;
        ret = min(ret, dfs(nxtd, nxt, s, t, maxd)); //constrain here is ok, too, or use minus to zero
        if(ret == -1) break; //this may reduce node expanded
    }
    cur_node_expanded--;
    if(ret != -1) vis[cor(s)] = pii(-1,-1); //if not done, revover vis
    return ret;
}

pair<vector<pii>, int> IDA::solve(pii s, pii t, double TL)
{
    //TIMER(
    node_expanded = 0;
    cur_node_expanded = 0;
    max_node_expanded = 0;
    int maxd = h(s, t);
    while(1)
    {
        Solver::init();
        int res = dfs(h(s,t), s, s, t, maxd);
        if(res == -1) break;
        else if(res == INT_MAX) {cout << "no solution" << endl; break;}
        //maxd = res;
        //debug(maxd);
        //TIMER_C(checker)
        //if(checker > TL)
        //{
        //    cout << "TLE break at " << TL <<  " seconds";
        //break;
        //}
    }
    //)
    //print();
    vector<pii> path;
    construct_path(path, t);
    //debug(path); debug(maxd);
    assert(path.size() == maxd+1); // s -d++- 1 - 2 - 3 - d++ t 
    return mp(path, node_expanded);
}

#endif