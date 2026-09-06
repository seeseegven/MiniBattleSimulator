#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp);
	void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound, bool& isRunning);
	void CoutSkill(const std::string& s, int value, Skill* skill) override;
	void CoutSkill(const std::string& s, Skill* skill) override;
	void CoutSkillList(int curRound);
	void PrintCurrentRound(int curRound);
};
