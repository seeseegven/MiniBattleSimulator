#include "Enemy.h"
#include "Skill.h"
#include "Render.h"
#include <iostream>

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound)
{
	int index = ai.ChooseSkill(*this, *characters[0]);
	skills[index]->Use(*this, *characters[0]);
	Render::WaitForDisplay(1200);
}

void Enemy::CoutSkill(const std::string& s, int value, Skill* skill)
{
	std::cout << "\u654C\u4EBA\u4F7F\u7528 ";
	skill->SkillEffect(s, value);
}

void Enemy::CoutSkill(const std::string& s, Skill* skill)
{
}
