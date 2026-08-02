#include "Damage.h"

Damage::Damage(const std::string& s, std::function<int(Character&, Character&)> func) : Skill(s), damageFunc(func) {};

void Damage::Use(Character& caster, Character& target) {
	int damage = damageFunc(caster, target);
	target.TakeDamage(damage);
	CoutSkill(name, damage);
}

void Damage::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}