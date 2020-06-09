
//dependency
//#include "STcpClient.h"
//#include <stdlib.h>
//#include <iostream>
#include "mcts.h"

/*
    輪到此程式移動棋子
    board : 棋盤狀態(vector of vector), board[i][j] = i row, j column 棋盤狀態(i, j 從 0 開始)
            0 = 空、1 = 黑、2 = 白、-1 = 四個角落
    is_black : True 表示本程式是黑子、False 表示為白子

    return Step
    Step : vector, Step = {r, c}
            r, c 表示要下棋子的座標位置 (row, column) (zero-base)
*/
bool GetBoard(int idpackage, VVI&b, bool &is_black)
{
	b = VVI(BOARDSZ, vector<int>(BOARDSZ, 0));
	is_black = 1;
	return 1;
}

void SendStep(int idpackage, vector<int> step)
{
	cout << step[0] << " " << step[1] << endl;
	return;
}


std::vector<int> GetStep(std::vector<std::vector<int>>& brd, bool is_black) {
	MCTS agent;
	board b(brd);
	int pos = agent.best_action(b, is_black);
	return vector<int>({pos/BOARDSZ, pos%BOARDSZ});
}

int main() {
	int id_package = 1; //todo
	std::vector<std::vector<int>> board;
	std::vector<int> step;
	
	bool is_black;
	while (true) {
		if (GetBoard(id_package, board, is_black))
			break;

		step = GetStep(board, is_black);
		SendStep(id_package, step);
	}
}
