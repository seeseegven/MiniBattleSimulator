#pragma once
#include "Character.h"
#include <string>

class Skill {
public:
	Skill(const std::string& s) :name(s) {}
	virtual void Use(Character& caster, Character& target) = 0;
	virtual ~Skill()=default;
	virtual std::string GetName();
protected:
	std::string name;
};