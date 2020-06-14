#ifndef UCTH
#define UCTH

// dependency
#include "board.h"

//if define this, RAVE value will turn on
//#define USERAVEQ

#define BASENUM 10
#ifdef USERAVEQ
#define RBASENUM 10
#endif

#ifdef USERAVEQ
#define RAVEK 1000
#endif
//when use RAVE, c should be small mentioned by paper surveyed
#define UCB_C 0.25
#define INFQ 1000.0

typedef int Action; //for clarity

using namespace std;

//std::random_device rd;
//std::default_random_engine gen;

class Node
{
public:
  Node();
  ~Node();
  Node* parent; //its parent
  bool color; //last color
  Action pos; // last polay pos
  Node* mvc; // the index of most visited child, -1 = no children
  double num, cnt; //value;
  double log_cnt;

  #ifdef USERAVEQ
  double rnum, rcnt; //rave value, like after-Action Q-value IMO
  #endif

  int idx[BOARDVL+1]; //idx: board pos => cptr idx
  vector<Node*> cptr; //children of the node

  void initNode(Node* parent, Action i, bool c);
  int expand(board& b);
  void update(bool result);

  #ifdef USERAVEQ
  void rave_update(bool result);
  #endif

  Node* best_child();
  vector<double> getPi();
  inline double getQ();
  double show_stats();

private:
};


#endif //UCTH
