#include "Damage.h"
#include "Character.h"
#include "Render.h"
#include <iostream>

Damage::Damage(const std::string& s, const int round,
	const std::function<int(Character&, Character&)> func)
	: Skill(s, round), damageFunc(func)
{
}

void Damage::Use(Character& caster, Character& target)
{
	int damage = damageFunc(caster, target);
	target.TakeDamage(damage);
	caster.CoutSkill(name, damage, this);
}

int Damage::CalculateSkillScore(Character& caster, Character& target)
{
	return damageFunc(caster, target);
}

void Damage::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n\u9020\u6210\u4E86";
	Render::RenderText(std::to_string(value), TextColor::LightRed);
	std::cout << "\u70B9\u4F24\u5BB3\n";
}
