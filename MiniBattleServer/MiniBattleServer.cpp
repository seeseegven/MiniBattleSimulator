// MiniBattleServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include "Server.h"
#include "BattleManager.h"

#pragma comment(lib, "ws2_32.lib")





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
    SOCKET clientSocket1 = server->AcceptClient();
    if (clientSocket1 == INVALID_SOCKET) {
        std::cout << "accept failed\n";
    }
    else {
        std::cout << "Client connected!\n";
    }
    while (1) {
        std::string reply = "Hello Client1";
        std::string buffer(1024, '\0');
        int rec = server->Receive(clientSocket1, buffer);
        if (rec <= 0) {
            std::cout << "客户端断开连接";
            break;
        }
        buffer.resize(rec);
        server->AnalysisMessage(buffer);
        std::string s = (server->GetBattleManager()->getManager()).StringToSend();
        server->Send(clientSocket1, s);
    }
    closesocket(clientSocket1);
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单
