#include "Character.h"

Character::Character(const std::string NameIn, const int HPIn,
	const int AttackIn, const int DefenseIn)
	: Name(NameIn), HP(HPIn),
	Attack(AttackIn),
	Defense(DefenseIn) {
}

bool Character::IsDead()
{
	return HP>0;
}

CharacterInfo Character::GetInfo()
{
	return {
		Name,
		HP,
		Attack,
		Defense
	};
}

void Character::SetHP(int hp)
{
	HP = hp > 100 ? 100 : hp;
}

void Character::SetDefense(int defense)
{
	Defense = defense;
}
