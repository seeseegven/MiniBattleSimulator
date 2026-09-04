#pragma once
#include <string>
#include <memory>
#include <queue>
#include <WinSock2.h>
#include <Windows.h>

class BattleManager;

struct PlayerMessage {
    int playerId;
    std::string message;
};

class Server {
public:
    Server();
    ~Server();
    bool Preparation();
    SOCKET AcceptClient();
    void SendMessages(SOCKET& s, const std::string& str);
    std::pair<bool, std::string> Receive(SOCKET& s);
    std::string AnalysisMessage(const std::string& str);
    auto& GetBattleManager() { return battleManager; };
    void AddClientToQueue(SOCKET s);
    void JoinBattle();
    void NewThread(SOCKET s, std::string str);
    void ManageBattleThread();
private:
    std::queue<SOCKET> waitQueue;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET client1Socket = INVALID_SOCKET;
    SOCKET client2Socket = INVALID_SOCKET;
    bool isStartUp = false;
    sockaddr_in serverAddr;
    std::unique_ptr<BattleManager> battleManager;
    std::queue<PlayerMessage> messages;
};