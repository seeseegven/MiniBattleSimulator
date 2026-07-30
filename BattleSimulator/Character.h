#pragma once
#include <string>
#include <iostream>

struct CharacterInfo {
	std::string Name;
	int HP, lastHP;
	int Attack, lastAttack;
	int Defense, lastDefense;
};

class Character
{
public:
	Character(const std::string NameIn, const int HPIn=100,
		const int AttackIn=30, const int DefenseIn=100);
	friend std::ostream& operator<<(std::ostream& os, Character& character);
	void TakeDamage(int demage);
    virtual void AttackOpponent(Character& target, int harm);
	bool IsDead();
	virtual ~Character() = default;
	CharacterInfo GetInfo();
	int ChangeHP(int HP, int lastHP);
	int ChangeAttack(int Attack, int lastAttack);
	int ChangeDefense(int Defense, int lastDefense);
protected:
	int Attack, lastAttack;
	int Defense, lastDefense;
	std::string Name;
	int HP;
	int lastHP;
};