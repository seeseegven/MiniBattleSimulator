#pragma once
#include <string>

class Character
{
public:
	Character(const std::string NameIn, const int HPIn = 100);

	void TakeDamage(int demage);

	virtual void Attack()=0;

	bool IsDead();

protected:
	std::string Name;

	int HP;
};