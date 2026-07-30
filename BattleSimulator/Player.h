#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(std::string name, int hp);

	void AttackOpponent(Character& target, int harm) override;
};