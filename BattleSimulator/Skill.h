#pragma once
#include <string>

class Character;

class Skill {
public:
	Skill(const std::string& s) :name(s) {}
	virtual void Use(Character& caster, Character& target) = 0;
	virtual ~Skill()=default;
	virtual std::string GetName();
	virtual int CalculateSkillScore(Character& caster, Character& target)=0;
protected:
	std::string name;
};