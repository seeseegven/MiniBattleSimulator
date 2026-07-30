#pragma once
#include "Character.h"
#include <string>

class Skill {
public:
	Skill(const std::string& s) :name(s) {}
	virtual void Use(Character& caster, Character& target) = 0;
	virtual ~Skill()=default;
	virtual void CoutSkill(const std::string& s, int value)=0;
protected:
	std::string name;
};