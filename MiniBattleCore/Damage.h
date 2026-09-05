#pragma once
#include "Skill.h"
#include <functional>

class Character;

class Damage : public Skill {
public:
	Damage(const std::string& s, const int round,
		const std::function<int(Character&, Character&)> func);
	void Use(Character& caster, Character& target) override;
	int CalculateSkillScore(Character& caster, Character& target) override;
	~Damage() override = default;
	void SkillEffect(const std::string& s, int value) override;
private:
	std::function<int(Character&, Character&)> damageFunc;
};
