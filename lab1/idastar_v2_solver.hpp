#ifndef IDA2_H
#define IDA2_H

#include "custom_header.hpp"

class IDA2 : public Solver
{
private:
    std::function<int(const pii&, const pii&)> h;
public:
    vector<pii> path;
    vector<vector<int>> dep; //relaxtion based
    //string name; this will cause the name be empty string
    IDA2();
    int dfs2(int d, pii s, pii t, int maxd);
    void init_dfs();
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
};

IDA2::IDA2()
{
    h = [&](const pii &s, const pii &t){
        return manhattan_distance(s, t)/3;
    };
    name = "IDA2";
}

int IDA2::dfs2(int d, pii s, pii t, int maxd) //s = current, p = from, d = current depth, t =  
{
    int ret = INT_MAX;
    if(d > maxd) return d;
    if(s == t) return -1;
    for(auto &di : dxdy)
    {
        pii nxt = s + di;
        if(!inrange(nxt)) continue;
        int nxtd = d + 1 - h(s,t) + h(nxt,t); 
        //nxt no relexation, no explore
        if(dep[cor(nxt)] <= nxtd) continue;
        path.pb(nxt);
        node_expanded++;
        cur_node_expanded++;
        max_node_expanded = max(max_node_expanded, cur_node_expanded);
        dep[cor(nxt)] = nxtd;
        ret = min(ret, dfs2(nxtd, nxt, t, maxd));
        if(ret == -1) break; //success, no pop_back this path
        path.pop_back();
        cur_node_expanded--;
    }
    return ret;
}

void IDA2::init_dfs()
{
    path.clear();
    int INF = N*N + N;
    dep = vector<vector<int>>(N, vector<int>(N, INF));
}


pair<vector<pii>, int> IDA2::solve(pii s, pii t, double TL)
{
    node_expanded = 0;
    max_node_expanded = 0;
    cur_node_expanded = 0;
    int maxd = h(s,t);
    while(1)
    {
        init_dfs();
        dep[cor(s)] = h(s,t);
        node_expanded++;
        cur_node_expanded++;
        max_node_expanded = max(max_node_expanded, cur_node_expanded);
        path.pb(s); //cleared before, no need pop
        int res = dfs2(h(s,t), s, t, maxd);
        if(res == -1) break;
        else if(res == INT_MAX) {cout << "no solution" << endl; break;}
        maxd = res;
    }
    assert(path.size() == maxd+1); // s -d++- 1 - 2 - 3 - d++ t 
    return mp(path, node_expanded);
}

#endif