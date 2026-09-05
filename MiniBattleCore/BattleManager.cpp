#include "BattleManager.h"
#include "Render.h"
#include <iostream>

void BattleManager::InitializeBattle(Mode mode)
{
	if (mode == Mode::pve) {
		auto p = std::make_unique<Player>("\u73A9\u5BB6", 100);
		player = p.get();
		manager.AddCharacter(std::move(p));
		auto e = std::make_unique<Enemy>("\u654C\u4EBA", 100);
		enemy = e.get();
		manager.AddCharacter(std::move(e));
	}
	else if (mode == Mode::pvp) {
		auto p = std::make_unique<Player>("\u73A9\u5BB61", 100);
		player = p.get();
		manager.AddCharacter(std::move(p));
		auto e = std::make_unique<Enemy>("\u73A9\u5BB62", 100);
		enemy = e.get();
		manager.AddCharacter(std::move(e));
	}
	manager.CoutInfo();
	player->InitSkill(*player, *enemy);
	enemy->InitSkill(*enemy, *player);
}

CharacterManager& BattleManager::getManager()
//后面的const暗含this指针，只有类里面函数可用。
//后面的const意思是不能修改类的成员变量
{
	return manager;
}

const std::string& BattleManager::GetLastBattleMessage() const
{
	return lastBattleMessage;
}

void BattleManager::ManageBattle()
{
	auto& characters = manager.GetCharacters();
	while (!player->IsDead() && !enemy->IsDead()) {
		player->PrintCurrentRound(curRound);
		CharacterInfo playerInfoBegin = characters[0]->GetInfo();
		CharacterInfo enemyInfoBegin = characters[1]->GetInfo();
		manager.Action(curRound);
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

bool BattleManager::ManageBattle(int playerId, const std::string& message)
{
	if (playerId != currentPlayer || message.size() != 1
		|| message[0] < '1' || message[0] > '5') {
		return false;
	}

	auto& characters = manager.GetCharacters();
	size_t casterIndex = static_cast<size_t>(playerId - 1);
	size_t targetIndex = casterIndex == 0 ? 1 : 0;
	size_t skillIndex = static_cast<size_t>(message[0] - '1');
	if (!characters[casterIndex]->UseSkill(skillIndex, *characters[targetIndex], curRound)) {
		return false;
	}
	lastBattleMessage = characters[casterIndex]->GetLastActionMessage();

	if (currentPlayer == 1) {
		currentPlayer = 2;
	}
	else {
		currentPlayer = 1;
		curRound++;
	}
	return true;
}
