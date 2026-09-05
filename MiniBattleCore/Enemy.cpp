#include "Enemy.h"
#include "Skill.h"

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::CoutSkill(const std::string& s, int value, Skill* skill)
{
	RecordActionMessage(skill->SkillEffect(s, value));
}

void Enemy::CoutSkill(const std::string& s, Skill* skill)
{
}
