#pragma once
#include <string>

class Character
{
public:
	Character(const std::string NameIn, const int HPIn = 100);

	void TakeDamage(int demage);

    virtual void Attack();

	bool IsDead();

	virtual ~Character() = default;
protected:
	std::string Name;

	int HP;
};