#include "BattleManager.h"

#include "Skill.h"

void BattleManager::InitializeBattle(Mode mode)
{
	if (mode == Mode::pve) {
		isPveRunning = true;
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

int BattleManager::GetCurrentRound() const
{
	return curRound;
}

std::vector<std::pair<std::string, int>> BattleManager::GetSkillInfo(int playerId) const
{
	Character* character = playerId == 1 ? static_cast<Character*>(player)
		: static_cast<Character*>(enemy);
	std::vector<std::pair<std::string, int>> skillInfo;
	for (const auto& skill : character->GetSkills()) {
		int roundLeft = skill->GetWhichRoundCanUse() - curRound;
		if (roundLeft < 0) {
			roundLeft = 0;
		}
		skillInfo.push_back({ skill->GetName(), roundLeft });
	}
	return skillInfo;
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
