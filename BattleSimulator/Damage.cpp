#include "Damage.h"
#include "Character.h"

Damage::Damage(const std::string& s, std::function<int(Character&, Character&)> func) : Skill(s), damageFunc(func) {};

void Damage::Use(Character& caster, Character& target) {
	int damage = damageFunc(caster, target);
	target.TakeDamage(damage);
	caster.CoutSkill(name, damage);
}

int Damage::CalculateSkillScore(Character& caster, Character& target) {
	return damageFunc(caster, target);
}

