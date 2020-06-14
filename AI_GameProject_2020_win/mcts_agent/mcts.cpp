#include "mcts.h"

#define DEBUG

#define TIME_LIMIT 0.8
//#define SHOW

/*
change to make for orthello

1.
board class
    rollout()
    just_play_color()
    check(pos, color)
    getv() getsimulation
    add(pos, color)
*/

void MCTS::init_with_board(board& b)
{
    root = new Node;
    //root_board = b; //copy a board from main
    root->initNode(nullptr, BOARDVL, b.just_play_color());
    //root->show_stats();
    //use NULL, BOARDSZ, 0, 0 for last action doesnt matter
    root->expand(b);
    //root->show_stats();
    total = 0;
}

void MCTS::reset(board& b)
{
    simu_board = b; //reset select simulation board(bpath, wpath will be rested)
    path.clear(); //clear select path
#ifdef USERAVEQ
    rave_path[0].clear();
    rave_path[1].clear();
#endif
}

Node* MCTS::select()
{
    Node* cur = root;
    path.push_back(cur);
    while (cur->cptr.size()) //if cptr.size() = 0, not expanded or game over
    {
        cur = cur->best_child();
        simu_board.add(cur->pos, cur->color);
#ifdef USERAVEQ
        rave_path[cur->color].push_back(cur->pos);
#endif
        path.push_back(cur);
    }
    return cur;
}

bool MCTS::roll_out() //the one in the board
{
    bool c = !simu_board.just_play_color(); //c = cur player to move
    int res = simu_board.simulate(c);
#ifdef USERAVEQ
    //update the simu actions to my rave_path vec
    //tree sim part in board b/wpath
    for (int i = 0; i < simu_board.bpsize; i++)
        rave_path[0].push_back(simu_board.bpath[i]);
    for (int i = 0; i < simu_board.wpsize; i++)
        rave_path[1].push_back(simu_board.wpath[i]);
#endif
    return res; //modified so that result is winner
}

void MCTS::backpropogation(bool res)
{
    //update the sim_tree part with path, and child's rave value with rave_path
    //rave_path[0/1][i] ~= path[i*2]
    for (int t = 0; t < path.size(); t++) {
        path[t]->update(res);
        //AMAF
        //if there is action A in the subtree from the afterstate S(color, pos) now
        //then Q(S(now),A) should be updated
        bool c = !path[t]->color; //the cur color to play(= children's color)
#ifdef USERAVEQ
        for (int tp = 0; tp < rave_path[c].size(); tp++)
        //tp=t/2=>subtree, tp=0=>all, should not influence the result because actionsi staken
        //2020/1/16 night, reading paper, get that this should influence
        {
            int k = path[t]->idx[rave_path[c][tp]];
            if (k != -1)
                path[t]->cptr[k]->rave_update(res);
        }
#endif
    }
}

int MCTS::best_action(board& init_b, int simu_per_step) 
{
    init_with_board(init_b); //create and expand root(null, basenum, p, c)
    time_t start_t, cur_t;
    start_t = clock();

#ifdef USEROUNDS
    for (int ep = 0; ep < simu_per_step; ep++) {
#endif
        //reset path, board
        reset(init_b);
        //selection
        Node* selected_root = select();
        //expansion
        bool res, nc;
        if (selected_root->cnt == BASENUM+1) { 
            int nc = selected_root->expand(simu_board);
            //debug(nc);
            //if there are children, one step look ahead
            //just expand => ravevalue as heuristic(can use other heuristic here?)
            if (nc != 0) {
                selected_root = selected_root->best_child();
                simu_board.add(selected_root->pos, selected_root->color);
#ifdef USERAVEQ
                rave_path[selected_root->color].push_back(selected_root->pos);
#endif
                path.push_back(selected_root);
            }
        }
        //simulation, with the intuition of two-go position is better
        res = roll_out();
        //backpropogation
        backpropogation(res);
        if((clock()-start_t)/CLOCKS_PER_SEC > TIME_LIMIT) break;
    }
    //return result, forget to judge NULL at first
    //best policy is of highest rave_winrate(in opening) and highest winrate(in ending)
    vector<double> pi = root->getPi();
    Action maxA = (root->mvc == nullptr) ? PASS : root->mvc->pos;
    //resign to speed up game process care /0
#ifdef RESIGN
    if (maxA != -1 && root->mvc->cnt != 0.0 && root->mvc->num / root->mvc->cnt < RESIGN)
    {
        debug("resign");
        maxA = -1;
    }
#endif
#ifdef SHOW
    cerr << endl;
    cur_t = clock();
    cerr << "simulations/sec : " << double(DEFAUT_SIMS) * CLOCKS_PER_SEC / double(cur_t - start_t) << endl;
    //cerr << "winrate(root_num/root/cnt) : " <<  <<endl;
    cerr << "show policy of the board:(double)" << endl;
    for (int ci = 0; ci < BOARDSZ; ci++) {
        for (int ri = 0; ri < BOARDSZ; ri++) {
            cerr << setw(3) << std::setprecision(3) << std::fixed << pi[ci * BOARDSZ + ri] << ' ';
        }
        cerr << endl;
    }
    cerr << "show policy of the board(int):" << endl;
    for (int ci = 0; ci < BOARDSZ; ci++) {
        for (int ri = 0; ri < BOARDSZ; ri++) {
            cerr << setw(3) << std::fixed << int(pi[ci * BOARDSZ + ri]*simu_per_step) << ' ';
        }
        cerr << endl;
    }
#endif
    //if(calc_winrate() < RESIGN) maxA = -1;
    //root->show_stats();
    clear();
    return maxA;
}

double MCTS::calc_winrate()
{
    return root->show_stats();
}

void MCTS::clear()
{
    delete root; //recursively delete by def of ~node
}
