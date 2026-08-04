#pragma once
#include "Character.h"
#include "EnemyAI.h"

class Enemy : public Character 
{
public:
	Enemy(std::string name, int hp);
	void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters);
private:
	EnemyAI ai;
};