#include "Character.h"
#include "BattleManager.h"
#include <iostream>

Character::Character(const std::string NameIn, const int HPIn)
	: attr(Attribution()),Name(NameIn), HP(HPIn), lastHP(HPIn) {}

void Character::TakeDamage(int demage) {
	lastHP = HP;
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

std::ostream& operator<<(std::ostream& os, Character& character) {
	os << "Name: " << character.Name << ", HP: ";
	int deltaHP = character.ChangeHP(character.lastHP, character.HP);
	if (deltaHP > 0) {
		BattleManager::RenderText(std::to_string(character.HP), TextColor::Green);
	}
	else if (deltaHP < 0) {
		BattleManager::RenderText(std::to_string(character.HP), TextColor::Red);
	}
	else {
		os << character.HP;
	}
	os << "Attack: " << character.attr.GetAttack() << ", Defense: " << character.attr.GetDefense() << "\n";
	return os;
}

int Character::ChangeHP(int lastHP, int HP) {
	return HP - lastHP;
}