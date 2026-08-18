#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA wsaData{};
	
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cout << "WSAStartUp failed\n";
		return 1;
	}

	SOCKET clientSocket = socket(
		AF_INET,
		SOCK_STREAM,
		IPPROTO_TCP
	);

	if (clientSocket == INVALID_SOCKET) {
		std::cout << "socket failed\n";
		WSACleanup();
		return 1;
	}

	sockaddr_in serverAddr{};
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8888);

	inet_pton(
		AF_INET,
		"127.0.0.1",
		&serverAddr.sin_addr
	);
	std::cout << "Connecting to server...\n";
	if (connect(clientSocket,
		reinterpret_cast<sockaddr*>(&serverAddr),
		sizeof(serverAddr))== SOCKET_ERROR) {
		std::cout << "connect failed\n";
		closesocket(clientSocket);
		WSACleanup();
		return 1;
	}

	std::cout << "connected to server!\n";
	while (1) {
		std::string message;
		std::cout << "请输入你要发送的内容,quit退出";
		std::cin >> message;
		if (message == "quit") break;
		send(clientSocket, message.data(), static_cast<int>(message.size()), 0);

		std::string buffer(1024, '\0');
		int received = recv(clientSocket, buffer.data(), buffer.size(), 0);
		if (received <= 0) {
			std::cout << "Server disconnected.\n";
			break;
		}
		buffer.resize(received);
		std::cout << "Server says: "
			<< buffer << '\n';
		Sleep(3000);
	}
	closesocket(clientSocket);
	WSACleanup();
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单  