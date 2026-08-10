#pragma once

class Character;



class EnemyAI {
public:
	EnemyAI() = default;
	int ChooseSkill(Character& caster, Character& target);
};