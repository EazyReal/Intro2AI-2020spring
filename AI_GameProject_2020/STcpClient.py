'''
    Copyright © 2019 by Phillip Chang
'''
import socket

socketServer = None
infoServer = ["localhost", 8888]
'''
    *   請將 idTeam 改成組別    *
'''
idTeam = -1

def _Connect(ip, port):
    socketCurrent = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    addrServer = (ip, port)
    error = socketCurrent.connect_ex(addrServer)
    if(error == 0):
        return socketCurrent
    
    socketCurrent.close()
    return None

def _RecvUntil(socketRecv, cntByte):
    if(socketRecv is None):
        return None
    try:
        rbData = socketRecv.recv(cntByte)
    except socket.error as _:
        return None
    
    if(len(rbData) != cntByte):
        return None

    return rbData

def _SendAll(socketSend, rbData):
    if(socketSend is None):
        return False
    try:
        resultSend = socketSend.sendall(rbData)
    except socket.error as e:
        print(e)
        return False

    return resultSend is None

import struct

def _ConnectToServer(cntRecursive = 0):
    global socketServer
    global infoServer
    global idTeam

    if(cntRecursive > 3):
        print("[Error] : maximum connection try reached!")
        return
    while(socketServer is None):
        socketServer = _Connect(infoServer[0], infoServer[1])

    structHeader = struct.Struct("i")
    rbHeader = structHeader.pack(idTeam)
    if(not _SendAll(socketServer, rbHeader)):
        socketServer.close()
        socketServer = None
        _ConnectToServer(cntRecursive + 1)

def _ReconnectToServer():
    global socketServer

    if(socketServer is not None):
        socketServer.close()
        socketServer = None
    
    _ConnectToServer()

'''
    取得當前遊戲狀態

    return (stop_program, id_package, board, is_black)
    stop_program : True 表示當前應立即結束程式，False 表示當前輪到自己下棋
    id_package : 當前棋盤狀態的 id，回傳移動訊息時需要使用
    board : 當前棋盤狀態 board[i][j] 表示棋盤第 i row, j column 上擺的棋子，0 表示沒有棋子、1 表示黑子、2 表示白子
    is_black : True 表示當前是輪到黑子，client 只有在輪到自己的時候才會收到遊戲狀態訊息
'''
def GetBoard():
    global socketServer

    if(socketServer is None):
        _ConnectToServer()
        if(socketServer is None):
            return (True, 0, None, None)
    
    # recv
    structHeader = struct.Struct("ii")
    structItem = struct.Struct("i")

    rbHeader = _RecvUntil(socketServer, structHeader.size)
    if(rbHeader is None):
        print("[Error] : connection lose, trying to reconnect...")
        socketServer.close()
        socketServer = None
        return GetBoard()
    
    (codeHeader, id_package) = structHeader.unpack(rbHeader)
    if(codeHeader == 0):
        return (True, 0, None, None)
    
    board = []
    for i in range(8):
        board.append([])
        for _ in range(8):
            rbBoard = _RecvUntil(socketServer, structItem.size)
            if(rbBoard is None):
                print("[Error] : connection lose, trying to reconnect...")
                socketServer.close()
                socketServer = None
                return GetBoard()
            itemBoard = structItem.unpack(rbBoard)[0]
            board[i].append(itemBoard)
    
    rbBlack = _RecvUntil(socketServer, structItem.size)
    if(rbBlack is None):
        print("[Error] : connection lose, trying to reconnect...")
        socketServer.close()
        socketServer = None
        return GetBoard()
    is_black = (structItem.unpack(rbBlack)[0] == 1)

    return (False, id_package, board, is_black)

'''
    向 server 傳達移動訊息
    id_package : 想要回復的訊息的 id_package
    Step = (r, c)
    r, c 表示要下的棋子座標 (row, column) (zero-base)

    return 函數是否執行成功
'''
def SendStep(id_package, Step):
    global socketServer

    if(socketServer is None):
        print("[Error] : trying to send step before connection is established")
        return
    
    # send
    structItem = struct.Struct("ii")

    rbHeader = structItem.pack(1, id_package)

    rbHeader += structItem.pack(Step[0], Step[1])

    # retry once
    if(not _SendAll(socketServer, rbHeader)):
        print("[Error] : connection lose, trying to reconnect")
        _ReconnectToServer()
