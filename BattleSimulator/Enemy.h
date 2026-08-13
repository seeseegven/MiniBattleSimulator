#pragma once
#include "Character.h"
#include "EnemyAI.h"

class Enemy : public Character 
{
public:
	Enemy(std::string name, int hp);
	void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound);
	void CoutSkill(const std::string& s, int value, Skill* skill) override;
private:
	EnemyAI ai;
};