
#include "STcpClient.h"
#include <stdlib.h>
#include <iostream>

/*
    輪到此程式移動棋子
    board : 棋盤狀態(vector of vector), board[i][j] = i row, j column 棋盤狀態(i, j 從 0 開始)
            0 = 空、1 = 黑、2 = 白、-1 = 四個角落
    is_black : True 表示本程式是黑子、False 表示為白子

    return Step
    Step : vector, Step = {r, c}
            r, c 表示要下棋子的座標位置 (row, column) (zero-base)
*/
std::vector<int> GetStep(std::vector<std::vector<int>>& board, bool is_black) {
	/*
	Example:
	std::vector<int> step;
	step.resize(2);

	step[0] = rand() % (7 + 1 - 0) + 0;
	step[1] = rand() % (7 + 1 - 0) + 0;
	return step;
	*/
}

int main() {
	int id_package;
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
