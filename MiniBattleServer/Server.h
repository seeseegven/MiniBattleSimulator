#pragma once
#include <string>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <WinSock2.h>
#include <Windows.h>

class BattleManager;
class Character;

struct PlayerMessage {
    int playerId;
    std::string message;
};//入队信息的数据结构

class Server {
public:
    Server();
    ~Server();
    bool Preparation();//初始化服务器设置
    SOCKET AcceptClient();//连接客户端服务器，并将其赋值给成员变量的socket并返回
    void SendMessages(SOCKET& s, const std::string& str);
    std::pair<bool, std::string> Receive(SOCKET& s);//接收数据，如果失败，返回false
    std::string AnalysisMessage(const std::string& str, int playerId);
    auto& GetBattleManager() { return battleManager; };
    void AddClientToQueue(SOCKET s);
    void JoinBattle();
    void NewThread(SOCKET s, std::string str);
    void ManageBattleThread();
    void InterruptBattle(SOCKET disconnected);
    void EndBattle(std::vector<std::unique_ptr<Character>>& characters);
private:
    std::mutex battleMutex;//锁battle
    std::mutex clientSocketMutex;
    std::queue<SOCKET> waitQueue;
    std::atomic_bool canRecv;
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET client1Socket = INVALID_SOCKET;
    SOCKET client2Socket = INVALID_SOCKET;
    bool isStartUp = false;//服务器是否已经开始
    bool isAdded = false;//客户端的操作是否已经入队
    std::atomic_bool isBattleRunning = false;//对局是否进行
    sockaddr_in serverAddr;
    std::unique_ptr<BattleManager> battleManager;
    std::queue<PlayerMessage> messages;
};
