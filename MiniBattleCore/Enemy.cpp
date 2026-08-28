#include "Enemy.h"

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}

void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound){}