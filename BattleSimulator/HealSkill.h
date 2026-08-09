#pragma once
#include <functional>
#include "Skill.h"


class HealSkill : public Skill {
public:
	HealSkill(const std::string& s);
	virtual void Effect(Character& caster, Character& target) = 0;
};

class Heal : public HealSkill {
public:
	Heal(const std::string& s, std::function<int(Character&, Character&)> func) 
		: HealSkill(s), Healfunc(func) {}
	void Effect(Character& caster, Character& target) override;//统一接口
	~Heal() override = default;
	virtual void Use(Character& caster, Character& target);
private:
	std::function<int(Character&, Character&)> Healfunc;
};

class DefenseUp : public HealSkill {
public:
	DefenseUp(const std::string& s, std::function<int(Character&, Character&)> func) 
		: HealSkill(s) , Defensefunc(func){}
	void Effect(Character& caster, Character& target) override;//target没必要，统一接口
	~DefenseUp() override = default;
	virtual void CoutSkill(const std::string& s, int value);
	virtual void Use(Character& caster, Character& target);
private:
	std::function<int(Character&, Character&)> Defensefunc;
};