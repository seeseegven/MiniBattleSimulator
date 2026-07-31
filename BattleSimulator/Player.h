#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp);
	void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters);
	void AttackOpponent(Character& target, int harm) override;
	void CoutSkillList();
};