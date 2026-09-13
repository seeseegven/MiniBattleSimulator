#pragma once
#include <string>
#include <atomic>
#include <queue>
#include <WinSock2.h>

enum ConnectStatus {
	InitFail,
	SocketFail,
	ConnectFail,
	ConnectSuccess
};

enum class NetModeState {
	error,
	success,
	interrupt,
	Win,
	Lose
};

class NetworkClient {
public:
	~NetworkClient();
	ConnectStatus Connect(const std::string& ip, int port);
	void CloseConnection();
	void SendMessages(const std::string& str);
	void DisplayConnectStatus(ConnectStatus status);
	std::string ReceiveMessage();
	void ReceiveAndUpdate();
	void ManageNetworkInput();
	NetModeState NetModeStateCheckReceivedValid(const std::string& s);
	//bool IsWaitingForInput() const { return isWaitingForInput.load(); }
private:
	void RequestDisconnect();
	COORD truePos;
	SOCKET clientSocket = INVALID_SOCKET;
	NetModeState battleState;
	std::queue<std::string> messages;
	std::atomic_bool isConnected{ false };
	std::atomic_bool canCin{ false };//收到信息后才能输入
	bool isWsaStarted = false;
	//多线程访问的变量最好用原子或加锁
	std::string previousCharacterData;
};

