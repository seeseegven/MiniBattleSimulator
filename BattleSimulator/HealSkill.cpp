#include "HealSkill.h"
#include "SkillFactory.h"
#include "Render.h"


HealSkill::HealSkill(const std::string& s) : Skill(s) {}

void Heal::Effect(Character& caster, Character& target) {
	auto info = caster.GetInfo();
	caster.SetHP(info.HP + 20);
	caster.CoutSkill(name, 20);
}

void DefenseUp::Effect(Character& caster, Character& target) {
	auto info = caster.GetInfo();
	caster.SetDefense(info.Defense + SkillFactory::CreateDefenseUp(caster, target));
	CoutSkill(name, 10);
}



void Heal::Use(Character& caster, Character& target) {
	CharacterInfo CasterInfo = caster.GetInfo();
	int heal = SkillFactory::CreateHealHP(caster, target);
	caster.SetHP(CasterInfo.HP + heal);
	caster.CoutSkill(name, heal);
}

int Heal::CalculateSkillScore(Character& caster, Character& target)
{
	return 100 - caster.GetInfo().HP;
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
	int defense = SkillFactory::CreateDefenseUp(caster, target);
	caster.SetDefense(info.Defense + defense);
	CoutSkill(name, defense);
}

int DefenseUp::CalculateSkillScore(Character& caster, Character& target)
{
	return 0;
}
