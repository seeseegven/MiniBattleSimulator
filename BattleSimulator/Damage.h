#pragma once
#include "Skill.h"
#include "Character.h"
#include "Render.h"
#include <string>

class Damage : public Skill {
public:
	Damage(const std::string& s);
	void Use(Character& caster, Character& target);
	void CoutSkill(const std::string& s, int value);
	//~Damage();
};