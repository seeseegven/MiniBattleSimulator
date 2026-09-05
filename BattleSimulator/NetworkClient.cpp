#include <iostream>
#include <WS2tcpip.h>
#include "NetworkClient.h"
#include "Render.h"

#pragma comment(lib, "ws2_32.lib")

ConnectStatus NetworkClient::Connect(const std::string& ip, int port)
{
	WSADATA wsaData{};

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return ConnectStatus::InitFail;
	}
	//错误代码，SOCKET clientSocket会导致同名局部变量覆盖
	clientSocket = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);

	if (clientSocket == INVALID_SOCKET) {
		WSACleanup();
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
		WSACleanup();
		return ConnectStatus::ConnectFail;
	}
	previousCharacterData.clear();
	isConnected = true;
	return ConnectStatus::ConnectSuccess;
}

void NetworkClient::SendMessages(const std::string& str)
{
	if (str == "quit") {
		std::cout << "客户端断开连接";
		isConnected = false;
		return;
	}
	send(clientSocket, str.data(), static_cast<int>(str.size()), 0);
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
	int received = recv(clientSocket, buffer.data(), buffer.size(), 0);
	if (received <= 0) {
		std::cout << "Server disconnected.\n";
		isConnected = false;
		return "";
	}
	buffer.resize(received);
	std::cout << "Server says: "
		<< buffer << '\n';
	return buffer;
}

void NetworkClient::ReceiveAndUpdate()
{
	//std::string s = ReceiveMessage();
	//Render::RenderText(s);
	while (isConnected) {
		
		std::string s = ReceiveMessage();
		if (!CheckReceivedValid(s)) {
			COORD pos = Render::GetCursorPosition();
			Render::SetCursorPosition(pos.X,pos.Y);
			Render::RenderText("当前不是你的回合\n");
			shouldHint = true;
			continue;
		}
		s = s.substr(s.find('|') + 1);
		size_t actionPosition = s.find('\n');
		std::string actionMessage;
		if (actionPosition != std::string::npos) {
			actionMessage = s.substr(actionPosition + 1);
			s = s.substr(0, actionPosition);
		}
		Render::ClearScreen();
		Render::DisplayAllCharacterInfo(s, previousCharacterData);
		previousCharacterData = s;
		if (!actionMessage.empty()) {
			Render::DisplayActionMessage(actionMessage);
		}
		shouldHint = true;
		if (!isConnected) {
			std::cout << "已退出联机\n";
			closesocket(clientSocket);
			Sleep(2000);
			break;
		}
	}
}

void NetworkClient::ManageNetworkInput()
{
	while (1) {
		if (isConnected && shouldHint) {
			std::string message;
			std::cout << "请输入你要发送的内容,quit退出\n";
			std::cin >> message;
			SendMessages(message);
			shouldHint = false;
		}
	}
}

bool NetworkClient::CheckReceivedValid(const std::string& s)
{
	size_t pos = s.find('|');
	if (s.substr(0, pos) == "Error")
		return false;
	return true;
}

