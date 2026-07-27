#pragma once
#include <string>
#include <iostream>
#include "Attribution.h"

class Character
{
public:
	Character(const std::string NameIn, const int HPIn = 100);

	void TakeDamage(int demage);

    virtual void Attack(Character& target);

	bool IsDead();

	virtual ~Character() = default;
	void Print();
	friend std::ostream& operator<<(std::ostream& os, const Character& character);
protected:
	Attribution attr;
	std::string Name;
	int HP;
};