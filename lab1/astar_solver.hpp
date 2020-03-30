#ifndef A_star_H
#define A_star_H

#include "custom_header.hpp"

class A_star : public Solver
{
public:
    //string name; this will cause the name be empty string
    A_star();
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
    void init();
    void print();
};

A_star::A_star()
{
    name = "A_star";
}

pair<vector<pii>, int> A_star::solve(pii s, pii t, double TL)
{
    node_expanded = 0;
    vector<pii> path;
    priority_queue<pii> q;
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

void A_star::init()
{
    vis = Board<pii>();
    rep(i, 0, N) fill(vis[i].begin(), vis[i].end(), pii(-1, -1));
    cout << name << " solver initialized." << endl;
}


void A_star::print()
{
    cout << "A_star_structure_test\n";
}

#endif