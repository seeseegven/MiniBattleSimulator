#pragma once
#include <string>
#include <WinSock2.h>

enum ConnectStatus {
	InitFail,
	SocketFail,
	ConnectFail,
	ConnectSuccess
};

class NetworkClient {
public:
	ConnectStatus Connect(const std::string& ip, int port);
	void SendMessage();
	void DisplayConnectStatus(ConnectStatus status);
	void ReceiveMessage();
	void ManageCommunication();
private:
	SOCKET clientSocket = INVALID_SOCKET;
	bool isConnected = false;
};