#include "Player.h"
#include "Skill.h"

Player::Player(std::string name, int hp) 
	: Character(name, hp) {}

void Player::CoutSkill(const std::string& s, int value, Skill* skill)
{
	RecordActionMessage(skill->SkillEffect(s, value));
}

void Player::CoutSkill(const std::string& s, Skill* skill)
{
}
