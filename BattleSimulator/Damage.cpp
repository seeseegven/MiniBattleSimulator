#include "Damage.h"

Damage::Damage(const std::string& s, int ratio) : Skill(s), ratio(ratio) {};

void Damage::Use(Character& caster, Character& target) {
	CharacterInfo CasterInfo = caster.GetInfo();
	int value = CalculateDamage(target);
	caster.AttackOpponent(target, value);
	CoutSkill(name, value);
}

void Damage::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}

int Damage::CalculateDamage(Character& target) {
	CharacterInfo TargetInfo = target.GetInfo();
	int value = ratio * 30 - TargetInfo.Defense * 0.1;
	return value;
}