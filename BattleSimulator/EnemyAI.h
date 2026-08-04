#pragma once

class Character;

enum class SkillType {
	Damage,
	Heal
};

class EnemyAI {
public:
	EnemyAI() = default;
	SkillType ChooseSkill(Character& enemy, Character& player);
};