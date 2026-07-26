#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"

class BattleManager
{
public:
	void InitializeBattle();
	void DisplayInfo();
	void ManageBattle();
private:
	ObjectManager manager;
	Player* player;
	Enemy* enemy;
};