#include "BattleManager.h"
#include "Game.h"
#include "Render.h"
#include <iostream>

void BattleManager::InitializeBattle() {
	auto p = std::make_unique<Player>("玩家", 100);
	player = p.get();
	auto e = std::make_unique<Enemy>("敌人", 100);
	enemy = e.get();
	manager.AddCharacter(std::move(p));
	manager.AddCharacter(std::move(e));
	//DisplayInfo();
	manager.CoutInfo();
	//初始化战局，把玩家和敌人加入管理器，并通过player和enemy成员进行操作
}


void BattleManager::ManageBattle() {
	while (!player->IsDead() && !enemy->IsDead()) {
		manager.Action();
		Render::ClearScreen();
		manager.CoutInfo();
	}
	if (player->IsDead()) {
		std::cout << "玩家死亡，游戏结束" << std::endl;
	}
	else {
		std::cout << "敌人死亡，玩家胜利" << std::endl;
	}
	std::cout << "按z返回菜单" << std::endl;
	char command;
	std::cin >> command;
	while (command != 'z') {
		std::cout << "按z返回菜单" << std::endl;
		std::cin >> command;
	}
}

