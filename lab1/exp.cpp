#include "custom_header.hpp"
#include "test_case_generator"

#include "bfs_solver.hpp"
#include "dfs_solver.hpp"
#include "iddfs_solver.hpp"
#include "astar_solver.hpp"
#include "idastar_solver.hpp"
#include <fstream>

#define N_TC 100

void test_solver(Solver* solver, int test_N, int n=N_TC)
{
    ofstream fs;
    RTCG gen;
    assert(fs.is_open());
    fs.open(solver->name + "_" + N +  "_data.csv");

    int total_node_expanded = 0;
    double total_time = 0.0;
    vector<pair<pii, pii>> tcs = gem.rtcs(n);
    vector<pair<double, double>> results(n);
    rep(i, 0, n)
    {
        auto ret = solver->solve(tcs[i].X, tcs[i].Y);
        total_node_expanded += ret.X;
        total_node_expanded += ;
    }

    fs << ", node_expanded, time_used" << endl;
    fs <<

    fs.close();
}

signed main()
{
    //list of solver names
    vector<Solver*> solvers;
    solvers.pb(new BFS());
    solvers.pb(new DFS());
    solvers.pb(new IDDFS());
    solvers.pb(new Astar());
    solvers.pb(new IDA());
    //rep(i, 0, solvers.size()) cout << "id " << i << ":, algorithm :" << solvers[i]->name << endl; 
    //cout << "input solver id:" << endl;
    int n_solver = solvers.size();
    rep(i, 0, n_solver)
    {
        test_solver(solvers[i]);
    }

    return 0;
}