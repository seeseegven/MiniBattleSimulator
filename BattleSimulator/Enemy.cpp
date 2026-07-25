#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::Attack(Character& target) {
	cout << Name << "ËºÒ§¹¥»÷" << endl;
	target.TakeDamage(15);
}