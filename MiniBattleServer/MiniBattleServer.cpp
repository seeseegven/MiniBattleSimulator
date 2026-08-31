// MiniBattleServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <thread>
#include "Server.h"
#include "BattleManager.h"

#pragma comment(lib, "ws2_32.lib")

void NewThread(Server& server, SOCKET s, std::string str)
{
    server.AnalysisMessage(str);
    while (1) {
        std::string reply = "Hello Client1";
        std::string buffer(1024, '\0');
        int rec = server.Receive(s, buffer);
        if (rec <= 0) {
            std::cout << "客户端断开连接";
            return;
        }
        buffer.resize(rec);
        server.AnalysisMessage(buffer);
        std::string strToSend = (server.GetBattleManager()->getManager()).StringToSend();
        server.Send(s, strToSend);
    }
    closesocket(s);
}

int main()
{
    auto server = std::make_unique<Server>();
    if (server->Preparation()) {
        std::cout << "Server is watting for client...\n";
    }
    else {
        std::cout << "Error. Please try again\n";
        return 1;
    }

    while (1) {
        SOCKET clientSocket1 = server->AcceptClient();
        if (clientSocket1 == INVALID_SOCKET) {
            std::cout << "accept failed\n";
            break;
        }
        else {
            std::cout << "Client connected!\n";
            std::thread t(
                NewThread,
                std::ref(*server),
                clientSocket1,
                "n"
            );
            t.detach();
        }
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
