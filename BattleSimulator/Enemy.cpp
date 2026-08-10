#include "Enemy.h"
#include "Damage.h"
#include "HealSkill.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}


void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	int index = ai.ChooseSkill(*this, *characters[0]);
	skills[index]->Use(*this, *characters[0]);
	Render::WaitForDisplay(1200);
}

void Enemy::CoutSkill(const std::string& s, int value) {
	std::cout << "敌人使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}