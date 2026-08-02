#include "Character.h"
#include "BattleManager.h"
#include <iostream>

Character::Character(const std::string NameIn, const int HPIn,
							const int AttackIn, const int DefenseIn)
	: Name(NameIn), HP(HPIn), lastHP(HPIn),
		Attack(AttackIn), lastAttack(AttackIn),
		Defense(DefenseIn), lastDefense(DefenseIn) {}

void Character::TakeDamage(int demage) {
	lastHP = HP;
	HP -= demage;
}


bool Character::IsDead() {
	return HP <= 0;
}

CharacterInfo Character::GetInfo() {
	return {
		Name,
		HP, lastHP,
		Attack, lastAttack,
		Defense, lastDefense
	};
}

int Character::IsChangeHP(int lastHP, int HP) {
	return HP - lastHP;
}

int Character::IsChangeAttack(int Attack, int lastAttack) {
	return Attack - lastAttack;
}

int Character::IsChangeDefense(int Defense, int lastDefense) {
	return Defense - lastDefense;
}

void Character::SetHP(int hp) {
	lastHP = HP;
	HP = hp;
}

void Character::SetDefense(int defense) {
	lastDefense = Defense;
	Defense = defense;
}
