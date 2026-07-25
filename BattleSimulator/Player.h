#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp);

	void Attack(Character& target) override;
};