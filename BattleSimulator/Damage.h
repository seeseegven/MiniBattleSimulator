#pragma once
#include "Skill.h"
#include <string>
#include <functional>

class Character;

class Damage : public Skill {
public:
	Damage(const std::string& s, const int round, const std::function<int(Character&, Character&)> func);
	void Use(Character& caster, Character& target) override;
	int CalculateSkillScore(Character& caster, Character& target) override;
	~Damage() override =default;
private:
	std::function<int(Character&, Character&)> damageFunc;
};