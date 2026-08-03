#pragma once
#include <string>
#include <iostream>
#include <vector>

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
	bool IsDead();
	virtual ~Character() = default;
	CharacterInfo GetInfo();
	int HpDeltaValue(int lastHP, int HP);
	int AttackDeltaValue(int Attack, int lastAttack);
	int DefenseDeltaValue(int Defense, int lastDefense);
	void SetHP(int hp);
	void SetDefense(int defense);
	virtual void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) = 0;
protected:
	int Attack, lastAttack;
	int Defense, lastDefense;
	std::string Name;
	int HP;
	int lastHP;
};