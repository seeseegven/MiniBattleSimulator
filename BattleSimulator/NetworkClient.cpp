#include <iostream>
#include <WS2tcpip.h>
#include "NetworkClient.h"
#include "Render.h"

#pragma comment(lib, "ws2_32.lib")

NetworkClient::~NetworkClient()
{
	CloseConnection();
	if (isWsaStarted) {
		WSACleanup();
		isWsaStarted = false;
	}
}

ConnectStatus NetworkClient::Connect(const std::string& ip, int port)
{
	if (!isWsaStarted) {
		WSADATA wsaData{};
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
			return ConnectStatus::InitFail;
		}
		isWsaStarted = true;
	}

	CloseConnection();
	//错误代码，SOCKET clientSocket会导致同名局部变量覆盖
	clientSocket = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);

	if (clientSocket == INVALID_SOCKET) {
		return ConnectStatus::SocketFail;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);

	inet_pton(
		AF_INET,
		ip.data(),
		&serverAddr.sin_addr
	);
	std::cout << "Connecting to server...\n";
	if (connect(clientSocket,
		reinterpret_cast<sockaddr*>(&serverAddr),
		sizeof(serverAddr)) == SOCKET_ERROR) {
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
		return ConnectStatus::ConnectFail;
	}
	previousCharacterData.clear();
	shouldHint = false;
	isWaitingForInput = false;
	isConnected = true;
	return ConnectStatus::ConnectSuccess;
}

void NetworkClient::RequestDisconnect()
{
	isConnected = false;
	shouldHint = false;
	if (clientSocket != INVALID_SOCKET) {
		shutdown(clientSocket, SD_BOTH);
	}
}

void NetworkClient::CloseConnection()
{
	RequestDisconnect();
	if (clientSocket != INVALID_SOCKET) {
		closesocket(clientSocket);
		clientSocket = INVALID_SOCKET;
	}
}

void NetworkClient::SendMessages(const std::string& str)
{
	if (!isConnected) {
		return;
	}
	if (send(clientSocket, str.data(), static_cast<int>(str.size()), 0)
		== SOCKET_ERROR) {
		std::cout << "发送失败，连接已断开\n";
		RequestDisconnect();
	}
}

void NetworkClient::DisplayConnectStatus(ConnectStatus status)
{
	if (status == ConnectStatus::InitFail) std::cout << "WSAStartUp failed\n";
	else if (status == ConnectStatus::SocketFail) std::cout << "socket failed\n";
	else if (status == ConnectStatus::ConnectFail) std::cout << "connect failed\n";
	else std::cout << "connected to server!\n等待服务器分配\n";
}

std::string NetworkClient::ReceiveMessage()
{
	std::string buffer(1024, '\0');
	int messageSize = 0;
	while (buffer.find('\r') == std::string::npos) {
		if (messageSize == buffer.size()) {
			std::cout << "服务器消息超过接收上限\n";
			RequestDisconnect();
			return "";
		}
		int received = recv(clientSocket, buffer.data()+messageSize, 
			static_cast<int>(buffer.size()-messageSize), 0);
		if (received <= 0) {
			if (isConnected) {
				std::cout << "Server disconnected.\n";
			}
			isConnected = false;
			shouldHint = false;
			return "";
		}
		messageSize += received;
	}
	buffer.resize(buffer.find('\r'));
	
	return buffer;
}

void NetworkClient::ReceiveAndUpdate()
{
	//std::string s = ReceiveMessage();
	//Render::RenderText(s);
	while (isConnected) {
		
		std::string s = ReceiveMessage();
		if (!isConnected || s.empty()) {
			break;
		}

		NetModeState state = NetModeStateCheckReceivedValid(s);
		if (state == NetModeState::error) {
			COORD curPos = Render::GetCursorPosition();
			Render::HintAndResetCursor(curPos.Y-truePos.Y, "当前不是你的回合\n");
			shouldHint = true;
			continue;
		}
		else if (state == NetModeState::interrupt) {
			isConnected = false;
			shouldHint = false;
			Render::RenderText("由于玩家退出，对局结束\n");
			break;
		}
		else if (state == NetModeState::Lose) {
			shouldHint = false;
			Render::RenderText("你输了，按任意键返回\n");
			break;
		}
		else if (state == NetModeState::Win) {
			shouldHint = false;
			Render::RenderText("恭喜你赢了，按任意键返回\n", TextColor::LightMagenta);
			char s;
			std::cin >> s;
			break;
		}
		s = s.substr(s.find('|') + 1);
		size_t roundPosition = s.find('|');
		int currentRound = std::stoi(s.substr(0, roundPosition));
		s = s.substr(roundPosition + 1);
		size_t skillPosition = s.find('|');
		std::string skillData = s.substr(0, skillPosition);
		s = s.substr(skillPosition + 1);
		size_t actionPosition = s.find('\n');
		std::string actionMessage;
		if (actionPosition != std::string::npos) {
			actionMessage = s.substr(actionPosition + 1);
			s = s.substr(0, actionPosition);
		}
		Render::ClearScreen();
		std::cout << "进入战斗   quit退出" << std::endl;
		Render::DisplayAllCharacterInfo(s, previousCharacterData);
		previousCharacterData = s;
		if (!actionMessage.empty()) {
			Render::DisplayActionMessage(actionMessage);
		}
		Render::DisplayCurrentRound(currentRound);
		Render::DisplaySkillList(skillData);
		truePos = Render::GetCursorPosition();
		shouldHint = true;
	}
	isConnected = false;
	shouldHint = false;
}

void NetworkClient::ManageNetworkInput()
{
	while (1) {
		if (!isConnected) break;
		if (shouldHint) {
			std::string message;
			isWaitingForInput = true;
			if (!isConnected) {
				isWaitingForInput = false;
				break;
			}
			if (!(std::cin >> message)) {
				isWaitingForInput = false;
				RequestDisconnect();
				break;
			}
			isWaitingForInput = false;
			if (!isConnected) {
				break;
			}
			if (message == "quit") {
				std::cout << "客户端断开连接\n";
				RequestDisconnect();
				break;
			}
			if (!(message > "0" && message < "6")) {
				COORD curPos = Render::GetCursorPosition();
				Render::HintAndResetCursor(curPos.Y-truePos.Y, "无效技能\n");
				continue;
			}
			SendMessages(message);
			shouldHint = false;
		}
		else {
			Sleep(10);
		}
	}
}



NetModeState NetworkClient::NetModeStateCheckReceivedValid(const std::string& s)
{
	size_t pos = s.find('|');
	if (s.substr(0, pos) == "Error")
		return NetModeState::error;
	else if (s.substr(0, pos) == "Interrupt") {
		return NetModeState::interrupt;
	}
	else if (s.substr(0, pos) == "Win") {
		return NetModeState::Win;
	}
	else if (s.substr(0, pos) == "Dead") {
		return NetModeState::Lose;
	}
	return NetModeState::success;
}

