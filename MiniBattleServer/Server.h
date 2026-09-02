#pragma once
#include <string>
#include <memory>
#include <queue>
#include <WinSock2.h>
#include <Windows.h>

class BattleManager;

class Server {
public:
    Server();
    ~Server();
    bool Preparation();
    SOCKET AcceptClient();
    void Send(SOCKET& s, const std::string& str);
    int Receive(SOCKET& s, std::string& str);
    std::string AnalysisMessage(const std::string& str);
    auto& GetBattleManager() { return battleManager; };
    void AddClientToQueue(SOCKET s);
    void JoinBattle();
    void NewThread(SOCKET s, std::string str);
private:
    std::queue<SOCKET> waitQueue;
    SOCKET listenSocket = INVALID_SOCKET;
    bool isStartUp = false;
    sockaddr_in serverAddr;
    std::unique_ptr<BattleManager> battleManager;
};