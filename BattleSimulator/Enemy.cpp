#include "Enemy.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::AttackOpponent(Character& target, int harm) {
	cout << Name << "撕咬攻击" << endl;
	target.TakeDamage(15);
}

void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	characters[1]->AttackOpponent(*characters[0], 15);
	std::cout << "敌人进行普攻，造成了";
	Render::RenderText("15", TextColor::Red);
	std::cout << "点伤害" << std::endl;
	Render::WaitForDisplay(1200);
}