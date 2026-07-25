#include "Character.h"
#include <iostream>

Character::Character(const std::string NameIn, const int HPIn)
	: Name(NameIn), HP(HPIn) {}

void Character::TakeDamage(int demage) {
	HP -= demage;
}

void Character::Attack(Character& target) {
	// Ä¬ÈÏ¹¥»÷ÐÐÎª
	target.TakeDamage(10);
}

bool Character::IsDead() {
	return HP <= 0;
}

void Character::Print() {
	std::cout << "Name: " << Name << ", HP: " << HP << std::endl;
}