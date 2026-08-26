// MiniBattleServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Windows.h>
#include "Test.h"

#pragma comment(lib, "ws2_32.lib")

void Send(SOCKET& s, const std::string& str) {
    //把str发送到SOCKET s那边
    send(
        s,
        str.data(),
        static_cast<int>(str.size()),
        0
    );
}

int Receive(SOCKET& s,  std::string& str) {
    int received = recv(
        s,
        str.data(),
        static_cast<int>(str.size()),
        0
    );//从clientSocket1接收最多1023字节放入buffer，返回值是实际收到了多少字节
    if (received > 0) {
        str.resize(received);
        std::cout << "Client says: "
            << str << "\n";
    }
    return received;
}

void AnalysisMessage(const std::string& str) {
    if (str.size() == 1 && str[0] == 'n') {
        test t = testInit(Mode::pvp);
        std::cout << t.x << "     ghjfdh    " << t.y;
    }
}

int main()
{
    //初始化winsock
    WSADATA wsaData{};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartUp failed" << std::endl;
        return 1;
    }

    SOCKET listenSocket = socket(
        AF_INET,//ipv4
        SOCK_STREAM,//字节流
        IPPROTO_TCP//tcp协议
    );

    if (listenSocket == INVALID_SOCKET) {
        std::cout << "socket failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr),
        sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cout << "bind failed\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "listen failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is watting for client...\n";

    SOCKET clientSocket1 = accept(listenSocket, nullptr, nullptr);
    if (clientSocket1 == INVALID_SOCKET) {
        std::cout << "accept failed\n";
    }
    else {
        std::cout << "Client connected!\n";
        std::string reply = "Hello Client1";
        std::string buffer(1024, '\0');
        while (1) {
            Send(clientSocket1, reply);
            int rec = Receive(clientSocket1, buffer);
            if (rec <= 0) {
                std::cout << "客户端断开连接";
                break;
            }
            buffer.resize(rec);
            AnalysisMessage(buffer);
        }
        closesocket(clientSocket1);
        
        WSACleanup();
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
