#ifndef Astar_H
#define Astar_H

#include "custom_header.hpp"

class Astar : public Solver
{
private:
    std::function<int(const pii&, const pii&)> h;
public:
    //string name; this will cause the name be empty string
    Astar();
    pair<vector<pii>, int> solve(pii x, pii y, double TL);
    //int h1(pii x); //heuristic
};

Astar::Astar()//std::function<int(pii)> _h)
{
    h = [&](const pii &s, const pii &t){
        return manhattan_distance(s, t)/3;
    };
    name = "Astar";
}

pair<vector<pii>, int> Astar::solve(pii s, pii t, double TL)
{
    TIMER_S
    node_expanded = 0;
    cur_node_expanded = 0;
    max_node_expanded = 0;
    vector<pii> path;
    priority_queue<pair<int, pair<int, int>>> pq; //bigger first out 
    //note: negate the sum of heuristic + distance now, to arvhieve smaller first out
    //origially, nxt_h = cur_h - h(cur, t) + 1 + h(nxt, t)
    //now, nxt_h = cur_h - 1 + h(cur, t) - h(nxt, t)
    pq.push(mp(-h(s,t), s));
    node_expanded++;
    cur_node_expanded++;
    vis[cor(s)] = s;
    while(!pq.empty())
    {
        pair<int, pii> cur = pq.top(); pq.pop();
        cur_node_expanded--;
        if(cur.Y == t) break;
        for(auto &d : dxdy)
        {
            pii nxtp = cur.Y + d;
            if(!inrange(nxtp) || vis[cor(nxtp)] != pii(-1,-1)) continue;
            //if(nxt == t) 
            pair<int, pii> nxt = mp(cur.X-1+h(cur.Y, t)-h(nxtp, t), nxtp);
            pq.push(nxt);
            node_expanded++;
            cur_node_expanded++;
            max_node_expanded = max(max_node_expanded, cur_node_expanded);
            vis[cor(nxtp)] = cur.Y;
        }
    }
    TIMER_C(_t)
    TIMER_P(_t)
    Solver::construct_path(path, t);

    return mp(path, node_expanded);
}

#endif