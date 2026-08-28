#pragma once
#include "CharacterManager.h"

enum  class Mode
{
	pvp,
	pve
};

class BattleManager {
public:
	void InitializeBattle(Mode mode);
	//void DisplayInfo();
	//void ManageBattle();
	CharacterManager& getManager();
private:
	CharacterManager manager;
	int curRound = 0;//当前回合
	//Player* player;
};