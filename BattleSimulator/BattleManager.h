#pragma once
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"


class BattleManager
{
public:
	void InitializeBattle();
	//void DisplayInfo();
	void ManageBattle();
	void PrintCurrentRound();
	int GetCurRound();
private:
	ObjectManager manager;
	int curRound=0;//当前回合
	Player* player;
	Enemy* enemy;
};