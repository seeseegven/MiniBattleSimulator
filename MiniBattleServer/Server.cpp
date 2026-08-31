#include <iostream>
#include "Server.h"
#include "BattleManager.h"



Server::Server(const std::string& r, Flag f):serverAddr(sockaddr_in{})
{
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

Server::~Server()
{
    if (listenSocket != INVALID_SOCKET) {
        closesocket(listenSocket);
        listenSocket = INVALID_SOCKET;
    }
    if (isStartUp) {
        WSACleanup();
        isStartUp = false;
    }
}

bool Server::Preparation()
{
    //初始化winsock
    WSADATA wsaData{};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "WSAStartUp failed" << std::endl;
        return 0;
    }
    isStartUp = true;
    listenSocket = socket(
        AF_INET,//ipv4
        SOCK_STREAM,//字节流
        IPPROTO_TCP//tcp协议
    );

    if (listenSocket == INVALID_SOCKET) {
        std::cout << "socket failed\n";
        WSACleanup();
        return 0;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr),
        sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "bind failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "listen failed\n";
        closesocket(listenSocket);
        WSACleanup();
        return 0;
    }
    return 1;
}

SOCKET Server::AcceptClient()
{
    return accept(listenSocket, nullptr, nullptr);
}

void Server::Send(SOCKET& s, const std::string& str) {
    //把str发送到SOCKET s那边
    send(
        s,
        str.data(),
        static_cast<int>(str.size()),
        0
    );
}

int Server::Receive(SOCKET& s, std::string& str) {
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

void Server::AnalysisMessage(const std::string& str) {
    if (str.size() == 1 && str[0] == 'n') {
        battleManager = std::make_unique<BattleManager>();
        battleManager->InitializeBattle(Mode::pvp);
    }
    else {

    }
}




