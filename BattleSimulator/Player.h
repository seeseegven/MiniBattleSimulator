#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp);
	void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound);
	void CoutSkill(const std::string& s, int value) override;
	void CoutSkillList(int curRound);
};