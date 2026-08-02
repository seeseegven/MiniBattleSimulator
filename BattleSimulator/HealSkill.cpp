#include "HealSkill.h"
#include "Render.h"


HealSkill::HealSkill(const std::string& s) : Skill(s) {}

void Heal::Effect(Character& caster) {
	auto info = caster.GetInfo();
	caster.SetHP(info.HP + 20);
	CoutSkill(name, 20);
}

void DefenseUp::Effect(Character& caster) {
	auto info = caster.GetInfo();
	info.Defense += 10;
}

void Heal::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightGreen);
	std::cout << ",\n恢复了";
	Render::RenderText(std::to_string(value), TextColor::Green);
	std::cout << "点血量\n";
}

void Heal::Use(Character& caster, Character& target) {
	
}