#pragma once
#include <string>

class Character
{
public:
	Character(const std::string NameIn, const int HPIn = 100);

	void TakeDamage(int demage);

    virtual void Attack(Character& target);

	bool IsDead();

	virtual ~Character() = default;
	void Print();
protected:
	std::string Name;

	int HP;
};