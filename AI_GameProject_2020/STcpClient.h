//
//	Copyright © 2019 by Phillip Chang
//
#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

#include <cstdio>
#include <vector>

SOCKET socketServer = INVALID_SOCKET;
const char *infoServer[] = { "localhost", "8888" };
/*
	請將 idTeam 改成組別
*/
int idTeam = 41;

class _WSAData {
public:
	_WSAData() {
		if (WSAStartup(MAKEWORD(2, 2), &wsadata_) != 0) {
			printf("WSAStartup Fail %d", WSAGetLastError());
		}
	}
	~_WSAData() {
		WSACleanup();
	}
private:
	WSADATA wsadata_;
}initializerWSA;

SOCKET _CreateConnectSocket(const char* strIp, const char* strPort) {
	addrinfo addrinfoHint, *listDestAddrinfo = NULL, *addrinfoIterator = NULL;
	ZeroMemory(&addrinfoHint, sizeof(addrinfo));
	addrinfoHint.ai_family = AF_INET;
	addrinfoHint.ai_socktype = SOCK_STREAM;
	addrinfoHint.ai_protocol = IPPROTO_TCP;
	int errorApi = getaddrinfo(strIp, strPort, &addrinfoHint, &listDestAddrinfo);
	if (errorApi != 0) return INVALID_SOCKET;
	//	create socket
	SOCKET socketResult = socket(listDestAddrinfo->ai_family, listDestAddrinfo->ai_socktype, listDestAddrinfo->ai_protocol);
	if (socketResult == INVALID_SOCKET) {
		freeaddrinfo(listDestAddrinfo);
		return INVALID_SOCKET;
	}
	//	try connect
	errorApi = SOCKET_ERROR;
	addrinfoIterator = listDestAddrinfo;
	while (addrinfoIterator != NULL) {
		errorApi = connect(socketResult, addrinfoIterator->ai_addr, (int)addrinfoIterator->ai_addrlen);
		if (errorApi != SOCKET_ERROR) break;
		addrinfoIterator = addrinfoIterator->ai_next;
	}
	freeaddrinfo(listDestAddrinfo);
	if (errorApi == SOCKET_ERROR) {
		closesocket(socketResult);
		socketResult = INVALID_SOCKET;
	}
	return socketResult;
}
bool _SendToSocket(SOCKET socketDest, size_t lengthSend, const BYTE* rbSend) {
	return send(socketDest, (const char*)rbSend, (int)lengthSend, 0) == lengthSend;
}
bool _RecvFromSocket(SOCKET socketSrc, size_t lengthRecv, BYTE* rbRecv) {
	return recv(socketSrc, (char*)rbRecv, (int)lengthRecv, MSG_WAITALL) == lengthRecv;
}

void _ConnectToServer(int cntRecursive = 0) {
	if (cntRecursive > 3) {
		printf("[Error] : maximum connection try reached!\n");
		return;
	}
	while (socketServer == INVALID_SOCKET)
		socketServer = _CreateConnectSocket(infoServer[0], infoServer[1]);

	if (!_SendToSocket(socketServer, sizeof(int), (BYTE*)&idTeam)) {
		closesocket(socketServer);
		socketServer = INVALID_SOCKET;
		_ConnectToServer(cntRecursive + 1);
	}
}

void _ReconnectToServer() {
	if (socketServer != INVALID_SOCKET) {
		closesocket(socketServer);
		socketServer = INVALID_SOCKET;
	}

	_ConnectToServer();
}

/*
	取得當前遊戲狀態

    return (stop_program), (id_package, board, is_black)
    stop_program : True 表示當前應立即結束程式，False 表示當前輪到自己下棋
    id_package : 當前棋盤狀態的 id，回傳移動訊息時需要使用
    board : 當前棋盤狀態 board[i][j] 表示棋盤第 i row, j column 上擺的棋子，0 表示沒有棋子、1 表示黑子、2 表示白子
    is_black : true 表示當前是輪到黑子，client 只有在輪到自己的時候才會收到遊戲狀態訊息
*/
bool GetBoard(int& id_package, std::vector<std::vector<int>>& board, bool& is_black) {
	if (socketServer == INVALID_SOCKET) {
		_ConnectToServer();
		if (socketServer == INVALID_SOCKET) {
			return true;
		}
	}
	BYTE rbHeader[8];
	if (!_RecvFromSocket(socketServer, 8, rbHeader)) {
		printf("[Error] : Connection lose, trying to reconnect...\n");
		closesocket(socketServer);
		socketServer = INVALID_SOCKET;
		return GetBoard(id_package, board, is_black);
	}
	int codeHeader = *((int*)rbHeader);
	id_package = *((int*)(rbHeader + 4));
	if (codeHeader == 0) return true;

	board.resize(8);
	for (int i = 0; i < 8; ++i) {
		board[i].resize(8);
		for (int j = 0; j < 8; ++j) {
			if (!_RecvFromSocket(socketServer, 4, (BYTE*)&(board[i][j]))) {
				printf("[Error] : Connection lose, trying to reconnect...\n");
				closesocket(socketServer);
				socketServer = INVALID_SOCKET;
				return GetBoard(id_package, board, is_black);
			}
		}
	}

	BYTE rbBlack[4];
	if (!_RecvFromSocket(socketServer, 4, rbBlack)) {
		printf("[Error] : Connection lose, trying to reconnect...\n");
		closesocket(socketServer);
		socketServer = INVALID_SOCKET;
		return GetBoard(id_package, board, is_black);
	}
	is_black = (*((int*)rbBlack)) == 1;

	return false;
}
/*
	向 server 傳達移動訊息
	id_package : 想要回復的訊息的 id_package
	listStep = <r, c>
	r, c 表示要移動的棋子座標 (row, column) (zero-base)
*/
void SendStep(int id_package, std::vector<int>& Step) {
	if (socketServer == INVALID_SOCKET) {
		printf("[Error] : trying to send step before connection is established\n");
		return;
	}

	std::vector<BYTE> rbData;
	rbData.resize(16);
	int* rbInsert = (int*)&(rbData[0]);
	*rbInsert++ = 1;
	*rbInsert++ = id_package;
	*rbInsert++ = Step[0];
	*rbInsert++ = Step[1];

	if (!_SendToSocket(socketServer, rbData.size(), &(rbData[0]))) {
		printf("[Error] : Connection lose, trying to reconnect\n");
		_ReconnectToServer();
	}
}
