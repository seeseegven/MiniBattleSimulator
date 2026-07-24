#include "Character.h"

Character::Character(const std::string NameIn, const int HPIn)
	: Name(NameIn), HP(HPIn) {}

void Character::TakeDamage(int demage) {
	HP -= demage;
}

bool Character::IsDead() {
	return HP <= 0;
}