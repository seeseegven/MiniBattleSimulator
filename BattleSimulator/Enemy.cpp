#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::Attack() {
	cout << "MonsterËºÒ§¹¥»÷" << endl;
}