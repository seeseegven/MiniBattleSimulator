#pragma once
#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"
#include <string>
#include <utility>
#include <vector>

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
	int GetCurrentRound() const;
	std::vector<std::pair<std::string, int>> GetSkillInfo(int playerId) const;
private:
	CharacterManager manager;
	bool isPveRunning = false;
	int curRound = 0;//当前回合
	int currentPlayer = 1;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	std::string lastBattleMessage;
};
