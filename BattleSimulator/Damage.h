#pragma once
#include "Skill.h"
#include "Character.h"
#include "Render.h"
#include <string>

class Damage : public Skill {
public:
	Damage(const std::string& s, int ratio);
	void Use(Character& caster, Character& target);
	void CoutSkill(const std::string& s, int value);
	virtual int CalculateDamage(Character& target);
	~Damage()=default;
private:
	int ratio;
};