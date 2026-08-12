#pragma once
#include <functional>
#include "Skill.h"

class Heal : public Skill {
public:
	Heal(const std::string& s, const int& round, 
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Healfunc(func) {
	}
	~Heal() override = default;
	virtual void Use(Character& caster, Character& target);
	int CalculateSkillScore(Character& caster, Character& target) override;
private:
	std::function<int(Character&, Character&)> Healfunc;
};

class DefenseUp : public Skill {
public:
	DefenseUp(const std::string& s, const int& round,
		std::function<int(Character&, Character&)> func) 
		: Skill(s, round) , Defensefunc(func){}
	~DefenseUp() override = default;
	virtual void CoutSkill(const std::string& s, int value);
	virtual void Use(Character& caster, Character& target);
	int CalculateSkillScore(Character& caster, Character& target) override;
private:
	std::function<int(Character&, Character&)> Defensefunc;
};