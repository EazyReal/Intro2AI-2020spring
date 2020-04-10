#include "custom_header.hpp"
#include "bfs_solver.hpp"
#include "dfs_solver.hpp"
#include "iddfs_solver.hpp"
#include "astar_solver.hpp"
#include "idastar_solver.hpp"

signed main()
{
    //interaction with cerr
    cerr << "Introduction to AI 2020 spring HW1 by yan-tong lin" << endl;
    cerr << "solver type list" << endl;
    //list of solver names
    vector<Solver*> solvers;
    solvers.pb(new BFS());
    solvers.pb(new DFS());
    solvers.pb(new IDDFS());
    solvers.pb(new Astar());
    solvers.pb(new IDA());
    N = 10; //effective test by dfs
    cerr << "input board size: ";
    cin >>  N;
    //iddfs test segment fault expected?, shouldnt it be TLE?
    rep(i, 0, solvers.size()) cerr << "id " << i << ":, algorithm :" << solvers[i]->name << endl; 
    cerr << "input solver id:" << endl;
    int id; int sx, sy, tx, ty;
    cin >> id;
    while(!(id>=0 && id < solvers.size()))
    {
        cerr << "input solver id in range:" << endl;
        cin >> id;
    }
    solvers[id]->init();
    cerr << "input start coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> sx >> sy;
    cerr << "input destination coordinate(0-indexed)(ex: 0 7):" << endl;
    cin >> tx >> ty;
    auto dat = solvers[id]->solve(mp(sx, sy), mp(tx, ty));
    vector<pii>& path = dat.X;
    int nodes_expanded = dat.Y;
    cerr << "tha path found by algorithm " << solvers[id]->name <<  " is of length " << path.size() << endl;
    cerr << "the past is listed as follow:\n";
    cerr << path;
    cerr << nodes_expanded << " " << solvers[id]->max_node_expanded << endl;

    //for real output
    cout << nodes_expanded << " " << solvers[id]->max_node_expanded << endl;

    return 0;
}