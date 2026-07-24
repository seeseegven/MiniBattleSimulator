#include "Character.h"
#include <iostream>

Character::Character(const std::string NameIn, const int HPIn)
	: Name(NameIn), HP(HPIn) {}

void Character::TakeDamage(int demage) {
	HP -= demage;
}

void Character::Attack() {
	// 默认攻击行为
	std::cout << "默认攻击" << std::endl;
}

bool Character::IsDead() {
	return HP <= 0;
}