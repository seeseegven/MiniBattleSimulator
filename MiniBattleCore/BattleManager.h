#pragma once
#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"
#include <string>

enum  class Mode
{
	pvp,
	pve
};

class BattleManager {
public:
	void InitializeBattle(Mode mode);
	void ManageBattle();
	bool ManageBattle(int playerId, const std::string& message);
	CharacterManager& getManager();
	const std::string& GetLastBattleMessage() const;
private:
	CharacterManager manager;
	int curRound = 0;//当前回合
	int currentPlayer = 1;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	std::string lastBattleMessage;
};
