#include "Damage.h"

Damage::Damage(const std::string& s) : Skill(s) {};

void Damage::Use(Character& caster, Character& target) {
	CharacterInfo CasterInfo = caster.GetInfo();
	CharacterInfo TargetInfo = target.GetInfo();
	int value = CasterInfo.Attack - TargetInfo.Defense * 0.1;
	caster.AttackOpponent(target, value);
	CoutSkill("技能1", value);
}

void Damage::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害";
}