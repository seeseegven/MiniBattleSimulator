#pragma once
#include <string>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
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
    std::string AnalysisMessage(const std::string& str, int playerId);
    auto& GetBattleManager() { return battleManager; };
    void AddClientToQueue(SOCKET s);
    void JoinBattle();
    void NewThread(SOCKET s, std::string str);
    void ManageBattleThread();
    void EndBattle(SOCKET disconnected);
private:
    std::mutex battleMutex;
    std::mutex clientSocketMutex;
    std::queue<SOCKET> waitQueue;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET client1Socket = INVALID_SOCKET;
    SOCKET client2Socket = INVALID_SOCKET;
    bool isStartUp = false;
    bool isAdded = false;//客户端的操作是否已经入队
    std::atomic_bool isBattleRunning = false;
    sockaddr_in serverAddr;
    std::unique_ptr<BattleManager> battleManager;
    std::queue<PlayerMessage> messages;
};
