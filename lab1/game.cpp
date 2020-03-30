#include "custom_header.hpp"
#include "bfs_solver.hpp"
#include "dfs_solver.hpp"
#include "iddfs_solver.hpp"

signed main()
{
    cout << "Introduction to AI 2020 spring HW1 by yan-tong lin" << endl;
    cout << "solver type list" << endl;
    //list of solver names
    vector<Solver*> solvers;
    solvers.pb(new BFS());
    solvers.pb(new DFS());
    solvers.pb(new IDDFS());
    rep(i, 0, solvers.size()) cout << "id " << i << ":, algorithm :" << solvers[i]->name << endl; 
    cout << "input solver id:" << endl;
    int id; int sx, sy, tx, ty;
    cin >> id;
    while(!(id>=0 && id < solvers.size()))
    {
        cout << "input solver id in range:" << endl;
        cin >> id;
    }
    solvers[id]->init();
    cout << "input start coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> sx >> sy;
    cout << "input destination coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> tx >> ty;
    auto dat = solvers[id]->solve(mp(sx, sy), mp(tx, ty));
    vector<pii>& path = dat.X;
    int nodes_expanded = dat.Y;
    cout << "tha path found by algorithm " << solvers[id]->name <<  " is of length " << path.size() << endl;
    cout << "the past is listed as follow:\n";
    cout << path;
    debug(nodes_expanded);

    return 0;
}