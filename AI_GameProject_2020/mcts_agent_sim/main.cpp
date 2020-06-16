#define MAC //if define this, mac testing
//#define TESTBOARD //if def this, will enter interactive board testing first
//#define LOG

#define MIX_AGENT 14 //define to -1 if do not want to use minmax in end game
//12

/*
 g++ -std=c++14  -o win.exe *.cpp -lWs2_32

output file name should contain 
author-team_no.-algorithm-timelimit-feature.exe

 C:\Windows\servicing\LCU\Package_for_RollupFix~31bf3856ad364e35~amd64~~17763.1282.1.9\wow64_microsoft-windows-w..nfrastructure-ws232_31bf3856ad364e35_10.0.17763.771_none_71b07ea3887c9605\r

cacls .\Sample1.exe /g everyone:f

check team_id, time, parameters everytime
UCB_C
H_INNER
RESIGN
TIMELIMIT

opion:
USE HERISTIC? (board)
MIX_AGENT?  (board)
MIN_MAX? (when MCTS use max) ()
MIN_MAX_THRESHOULD? (when MCTS use min max)
*/


//dependency
#ifndef MAC
#include "STcpClient.h"
#endif

#include "mcts.h"

/*
API of TA's program
    輪到此程式移動棋子
    board : 棋盤狀態(vector of vector), board[i][j] = i row, j column 棋盤狀態(i, j 從 0 開始)
            0 = 空、1 = 黑、2 = 白、-1 = 四個角落
    is_black : True 表示本程式是黑子、False 表示為白子

    return Step
    Step : vector, Step = {r, c}
            r, c 表示要下棋子的座標位置 (row, column) (zero-base)
*/

#ifdef MAC
bool GetBoard(int idpackage, VVI&b, bool &is_black)
{
	is_black = 1;
	b = VVI(BOARDSZ, vector<int>(BOARDSZ, 0));
	//cout << "interactive input for testing or empty board? (I/E):";
	// char op;
	// cin >> op;
	//if(op == 'I')
	//{
	trav(i,j) cin >> b[i][j];
	//}
	return 0;
}

void SendStep(int idpackage, vector<int> step)
{
	cout << step[0] << " " << step[1] << endl;
	return;
}
#endif

std::vector<int> GetStep(std::vector<std::vector<int>>& brd, bool is_black) {
	MCTS agent;
	board b(brd, is_black); // black to play => is_black = 1 => lastc = 1
	//b.print();
	int pos, value;
	if(b.empty_cnt() <= MIX_AGENT )
	{
#ifdef LOG
		cerr << "use mix agent" << endl;
#endif
		tie(pos, value) = min_max_agent(b, !b.lastc, 0);
	}
	pos = agent.best_action(b);
	return vector<int>({pos/BOARDSZ, pos%BOARDSZ});
}

int main() {
	int id_package = 1; //todo
	std::vector<std::vector<int>> b;
	std::vector<int> step;
	srand(time(NULL));

#ifdef TESTBOARD
	board bo;
	bo.simulate(BLACK);
	while(1)
	{
		cout << "enter x y (0-indexed) and color to move: \n";
		int x, y, c;
		cin >> x >> y >> c;
		bo.add(ID(x,y), c);
		bo.print();
	}
	VVI b;
#endif
	
	bool is_black;
	while (true) {
		if (GetBoard(id_package, b, is_black))
			break;
		step = GetStep(b, is_black);
#ifdef LOG
		cerr << "step: " << step[0] << " " << step[1] << endl;
#endif
		SendStep(id_package, step);
	}
}
/*
-1 0 0 0 0 0 0 -1
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0
-1 0 0 0 0 0 0 -1


-1 0 0 1 2 1 2 -1
1 2 1 2 2 1 2 1
0 2 0 1 2 1 2 2
0 1 0 0 1 2 1 2
2 1 1 1 2 1 1 2
1 2 2 2 1 2 0 1
2 1 1 1 1 1 2 0
-1 1 1 2 0 0 0 -1
*/