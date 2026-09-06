#include "BattleManager.h"
#include "Render.h"
#include <iostream>

void BattleManager::ManageBattle()
{
	auto& characters = manager.GetCharacters();
	while (!player->IsDead() && !enemy->IsDead()&&isPveRunning) {
		player->PrintCurrentRound(curRound);
		CharacterInfo playerInfoBegin = characters[0]->GetInfo();
		CharacterInfo enemyInfoBegin = characters[1]->GetInfo();
		manager.Action(curRound, isPveRunning);
		if (!isPveRunning) {
			return;
		}
		Render::ClearScreen();
		CharacterInfo playerInfoEnd = characters[0]->GetInfo();
		CharacterInfo enemyInfoEnd = characters[1]->GetInfo();
		std::cout << "\u8FDB\u5165\u6218\u6597   z\u9000\u51FA" << std::endl;
		Render::CoutCharacter(playerInfoBegin, playerInfoEnd);
		Render::CoutCharacter(enemyInfoBegin, enemyInfoEnd);
		curRound++;
	}
	if (player->IsDead()) {
		std::cout << "\u73A9\u5BB6\u6B7B\u4EA1\uFF0C\u6E38\u620F\u7ED3\u675F" << std::endl;
	}
	else {
		std::cout << "\u654C\u4EBA\u6B7B\u4EA1\uFF0C\u73A9\u5BB6\u80DC\u5229" << std::endl;
	}
	std::cout << "\u6309z\u8FD4\u56DE\u83DC\u5355" << std::endl;
	char command;
	std::cin >> command;
	while (command != 'z') {
		std::cout << "\u6309z\u8FD4\u56DE\u83DC\u5355" << std::endl;
		std::cin >> command;
	}
}
