#pragma once
#include <string>
#include <memory>
#include <WinSock2.h>
#include <Windows.h>

class BattleManager;

enum class Flag {
    greeting,
    init
};

class Server {
public:
    Server(const std::string& r = "Íæ¼ÒÄãºÃ", 
        Flag f = Flag::greeting);
    ~Server();
    bool Preparation();
    SOCKET AcceptClient();
    void Send(SOCKET& s, const std::string& str);
    int Receive(SOCKET& s, std::string& str);
    void AnalysisMessage(const std::string& str);
    auto& GetBattleManager() { return battleManager; };
private:
    SOCKET listenSocket = INVALID_SOCKET;
    bool isStartUp = false;
    sockaddr_in serverAddr;
    std::unique_ptr<BattleManager> battleManager;
};