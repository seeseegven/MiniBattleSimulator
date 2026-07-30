#pragma once
#include "Character.h"

class Enemy : public Character 
{
public:
		Enemy(std::string name, int hp);
		void AttackOpponent(Character& target, int harm) override;
};