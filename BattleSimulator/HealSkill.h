#pragma once
#include <functional>
#include "Skill.h"


class HealSkill : public Skill {
public:
	HealSkill(const std::string& s);
	virtual void Effect(Character& caster) = 0;
};

class Heal : public HealSkill {
public:
	Heal(const std::string& s, std::function<int(Character&, Character&)> func) : 
		HealSkill(s), healfunc(func) {}
	void Effect(Character& caster) override;
	~Heal() override = default;
	virtual void Use(Character& caster, Character& target);
private:
	std::function<int(Character&, Character&)> healfunc;
};

class DefenseUp : public HealSkill {
public:
	DefenseUp(const std::string& s) : HealSkill(s) {}
	void Effect(Character& caster) override;
	~DefenseUp() override = default;
	virtual void CoutSkill(const std::string& s, int value);
	virtual void Use(Character& caster, Character& target);
};