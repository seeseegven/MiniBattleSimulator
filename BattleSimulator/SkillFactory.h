#pragma once
#include <memory>
#include "Character.h"

class Skill;


class SkillFactory {
public:
	static int CreateFireBall(Character& caster, Character& target);
	static int CreateIceSword(Character& caster, Character& target);
	static int CreateOneTimeHealHP(Character& caster, Character& target);
	static int CreateDefenseUp(Character& caster, Character& target);
	static int CreateContinuousHealHP(Character& caster, Character& target);
};