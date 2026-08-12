#include "Damage.h"
#include "Character.h"

Damage::Damage(const std::string& s, const int round, 
	const std::function<int(Character&, Character&)> func)
	: Skill(s, round), damageFunc(func) {
};

void Damage::Use(Character& caster, Character& target) {
	int damage = damageFunc(caster, target);
	target.TakeDamage(damage);
	caster.CoutSkill(name, damage);
}

int Damage::CalculateSkillScore(Character& caster, Character& target) {
	return damageFunc(caster, target);
}

