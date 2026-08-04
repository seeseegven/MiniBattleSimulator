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
	caster.SetDefense(info.Defense + 10);
	CoutSkill(name, 10);
}

void Heal::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightGreen);
	std::cout << ",\n恢复了";
	Render::RenderText(std::to_string(value), TextColor::Green);
	std::cout << "点血量\n";
}

void Heal::Use(Character& caster, Character& target) {
	auto info = caster.GetInfo();
	caster.SetDefense(info.Defense + 10);
	CoutSkill(name, 10);
}

void DefenseUp::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightBlue);
	std::cout << ",\n防御力增加了";
	Render::RenderText(std::to_string(value), TextColor::LightBlue);
	std::cout << "点\n";
}

void DefenseUp::Use(Character& caster, Character& target) {
	auto info = caster.GetInfo();
	caster.SetDefense(info.Defense + 10);
	CoutSkill(name, 10);
}