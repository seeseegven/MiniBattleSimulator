#pragma once
#include <string>
#include <WinSock2.h>

enum ConnectStatus {
	InitFail,
	SocketFail,
	ConnectFail,
	ConnectSuccess
};

enum class NetModeState {
	waitForBattle,
	init
};

class NetworkClient {
public:
	ConnectStatus Connect(const std::string& ip, int port);
	void SendMessages(const std::string& str);
	void DisplayConnectStatus(ConnectStatus status);
	std::string ReceiveMessage();
	void ManageCommunication();
private:
	SOCKET clientSocket = INVALID_SOCKET;
	bool isConnected = false;
	NetModeState netState;
};