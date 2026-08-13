#include "Enemy.h"
#include "Damage.h"
#include "HealSkill.h"
#include "Render.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}


void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound) {
	int index = ai.ChooseSkill(*this, *characters[0]);
	skills[index]->Use(*this, *characters[0]);
	Render::WaitForDisplay(1200);
}

void Enemy::CoutSkill(const std::string& s, int value, Skill* skill) {
	std::cout << "µÐÈËÊ¹ÓÃ ";
	skill->SkillEffect(s, value);
}