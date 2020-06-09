
import STcpClient
import random

'''
    輪到此程式移動棋子
    board : 棋盤狀態(list of list), board[i][j] = i row, j column 棋盤狀態(i, j 從 0 開始)
            0 = 空、1 = 黑、2 = 白、-1 = 四個角落
    is_black : True 表示本程式是黑子、False 表示為白子

    return Step
    Step : single touple, Step = (r, c)
            r, c 表示要下棋子的座標位置 (row, column) (zero-base)
'''

def GetStep(board, is_black):
    """
    Example:
    x = random.randint(0, 7)
    y = random.randint(0, 7)
    return (x,y)
    """

while(True):
    (stop_program, id_package, board, is_black) = STcpClient.GetBoard()
    if(stop_program):
        break
    
    Step = GetStep(board, is_black)
    STcpClient.SendStep(id_package, Step)
