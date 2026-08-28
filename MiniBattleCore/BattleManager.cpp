#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"

void BattleManager::InitializeBattle(Mode mode)
{
	if (mode == Mode::pve) {
		auto p = std::make_unique<Player>("玩家", 100);
		manager.AddCharacter(std::move(p));
		auto e = std::make_unique<Enemy>("敌人", 100);
		manager.AddCharacter(std::move(e));
	}
	else if (mode == Mode::pvp) {
		auto p = std::make_unique<Player>("玩家1", 100);
		manager.AddCharacter(std::move(p));
		auto e = std::make_unique<Enemy>("玩家2", 100);
		manager.AddCharacter(std::move(e));
	}
}

CharacterManager& BattleManager::getManager()
//后面的const暗含this指针，只有类里面函数可用。
//后面的const意思是不能修改类的成员变量
{
	return manager;
}
