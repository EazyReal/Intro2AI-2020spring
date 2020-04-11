#include "custom_header.hpp"
//#include "test_case_generator.hpp"

#include "bfs_solver.hpp"
#include "dfs_solver.hpp"
#include "iddfs_solver.hpp"
#include "astar_solver.hpp"
#include "idastar_solver.hpp"
#include "dfsv2_solver.hpp"
#include "iddfs_v2_solver.hpp"
#include "idastar_v2_solver.hpp"
#include <fstream>

//0-indexed
int algoN = 4;
int minN = 5;
int maxN = 50;
int deltaN = 5;
int testN = 100;

string result_directory = "./results/";
string testcase_directory = "./testcases/";

void test_solver(Solver* solver)
{
    //RTCG gen; should not regen, should test on same dataset
    for(int ni = minN; ni <= maxN; ni += deltaN)
    {
        ifstream is;
        ofstream fs;
        //cerr << testcase_directory + "N" + to_string(ni) + ".txt" << endl;
        is.open(testcase_directory + "N" + to_string(ni) + ".txt");
        fs.open(result_directory + solver->name + "_N" + to_string(ni) + ".csv");
        assert(is.is_open());
        assert(fs.is_open());
        vector<int> time_statistics(testN);
        vector<int> mem_statistics(testN);
        double sum_time = 0.0;
        double sum_mem = 0.0;
        rep(i, 0, testN)
        {
            //is >> N chages board size!!
            pii s, t;
            is >> N >> s.X >> s.Y >> t.X >> t.Y;
            solver->init(); //N is set and use to init N size board
            auto ret = solver->solve(s, t);
            time_statistics[i] = solver->node_expanded;
            mem_statistics[i] = solver->max_node_expanded;
            sum_time += solver->node_expanded;
            sum_mem += solver->max_node_expanded;
            fs << solver->node_expanded << " "<< solver->max_node_expanded << endl;
        }
        sort(time_statistics.begin(), time_statistics.end());
        sort(mem_statistics.begin(), mem_statistics.end());
        fs << "node_expanded_min: " << time_statistics[0] << endl; 
        fs << "max_node_expanded_min: " << mem_statistics[0] << endl; 
        fs << "node_expanded_max: " << time_statistics[testN-1] << endl; 
        fs << "max_node_expanded_max: " << mem_statistics[testN-1] << endl; 
        fs << "node_expanded_medium: " << time_statistics[testN/2] << endl; 
        fs << "max_node_expanded_medium: " << mem_statistics[testN/2] << endl; 
        fs << "node_expanded_average: " << sum_time/double(testN) << endl; 
        fs << "max_node_expanded_average: " << sum_mem/double(testN) << endl; 

        fs.close();
    }
    return;
}

signed main()
{
    //list of solver names
    cin >> maxN >> deltaN >> testN; //passing hyper param from stdin
    vector<Solver*> solvers;
    solvers.pb(new BFS());
    solvers.pb(new DFS2());
    solvers.pb(new IDDFS2());
    solvers.pb(new Astar());
    solvers.pb(new IDA2());
    //rep(i, 0, solvers.size()) cout << "id " << i << ":, algorithm :" << solvers[i]->name << endl; 
    //cout << "input solver id:" << endl;
    int n_solver = solvers.size();
    rep(i, 0, n_solver)
    {
        test_solver(solvers[i]);
    }

    return 0;
}