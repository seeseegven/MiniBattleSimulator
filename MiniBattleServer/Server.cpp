#include <iostream>
#include <thread>
#include "Server.h"
#include "BattleManager.h"



Server::Server():serverAddr(sockaddr_in{})
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
    SOCKET clientSocket1 = accept(listenSocket, nullptr, nullptr);
    if (clientSocket1 == INVALID_SOCKET) {
        std::cout << "accept failed\n";
        return clientSocket1;
    }
    if (client1Socket == INVALID_SOCKET)
        client1Socket = clientSocket1;
    else if (client2Socket == INVALID_SOCKET)
        client2Socket = clientSocket1;
    return clientSocket1;
}

void Server::SendMessages(SOCKET& s, const std::string& str) {
    //把str发送到SOCKET s那边
    send(
        s,
        str.data(),
        static_cast<int>(str.size()),
        0
    );
}

std::pair<bool, std::string> Server::Receive(SOCKET& s) {
    std::string buffer(1024, '\0');
    int received = recv(
        s,
        buffer.data(),
        static_cast<int>(buffer.size()),
        0
    );//从clientSocket1接收最多1023字节放入buffer，返回值是实际收到了多少字节
    if (received <= 0) {
        return std::pair{ false, "" };
    }
    buffer.resize(received);
    std::cout << "Client says: "
            << buffer << "\n";
    return std::pair{ true, buffer };
}

std::string Server::AnalysisMessage(const std::string& str) {


    return (GetBattleManager()->getManager()).StringToSend(States::init);
}

void Server::AddClientToQueue(SOCKET s)
{
    waitQueue.push(s);
}

void Server::JoinBattle()
{
    if (waitQueue.size() < 2) {
        return;
    }
    battleManager = std::make_unique<BattleManager>();
    battleManager->InitializeBattle(Mode::pvp);
    std::thread battle(
        &Server::ManageBattleThread,
        this
    );
    battle.detach();
    std::string str = AnalysisMessage("b");
    while (!waitQueue.empty()) {
        SOCKET temp = waitQueue.front();
        std::thread t(
            &Server::NewThread,
            this,
            temp,
            str//传进去的是右值，要么ref引用要么const &
        );
        t.detach();
        waitQueue.pop();
    }   
}


void Server::NewThread(SOCKET s, std::string str)
{//客户端通信的单独线程
    SendMessages(s, str);
    while (1) {
        isAdded = false;
        auto  result = Receive(s);
        if (!result.first) {
            std::cout << "客户端断开连接\n";
            closesocket(s);
            return;
        }
        std::string& buffer(result.second);
        if (buffer.size() != 1 || buffer[0] < '1' || buffer[0]>'4') {
            SendMessages(s, "Invalid Skill\n");
            continue;
        }

        {
            std::lock_guard<std::mutex> lock(battleMutex);
            int id = 2;
            if (s == client1Socket) {
                id = 1;
            }
            if (!isAdded && whichClient % 2 == id % 2) {
                messages.push({ id, buffer });
                isAdded = true;
                whichClient += 1;
            }
        }
    }
}

void Server::ManageBattleThread()
{
    while (1) {
        if (!messages.empty()) {
            std::string str = messages.front().message;
            int id = messages.front().playerId;
            messages.pop();
            auto& effectCharacter = GetBattleManager()->getManager().GetCharacters()[id - 1];
            auto info = effectCharacter->GetInfo();
            effectCharacter->SetHP(info.HP - id);
            str = AnalysisMessage("b");
            SendMessages(client1Socket, str);
            SendMessages(client2Socket, str);
        }
    }
}




