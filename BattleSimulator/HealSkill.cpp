#include "HealSkill.h"
#include "SkillFactory.h"
#include "Render.h"
#include "EffectStatus.h"


void OneTimeHeal::Use(Character& caster, Character& target) {
	CharacterInfo CasterInfo = caster.GetInfo();
	int heal = SkillFactory::CreateOneTimeHealHP(caster, target);
	caster.SetHP(CasterInfo.HP + heal);
	caster.CoutSkill(name, heal, this);
}

int OneTimeHeal::CalculateSkillScore(Character& caster, Character& target)
{
	return 100 - caster.GetInfo().HP;
}

void DefenseUp::Use(Character& caster, Character& target) {
	auto info = caster.GetInfo();
	int defense = SkillFactory::CreateDefenseUp(caster, target);
	caster.SetDefense(info.Defense + defense);
	caster.CoutSkill(name, defense, this);
}

int DefenseUp::CalculateSkillScore(Character& caster, Character& target)
{
	return 0;
}

void DefenseUp::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n增加了";
	Render::RenderText(std::to_string(value), TextColor::LightBlue);
	std::cout << "点防御\n";
}

void ContinuousHeal::Use(Character& caster, Character& target) {
	CharacterInfo CasterInfo = caster.GetInfo();
	int heal = SkillFactory::CreateContinuousHealHP(caster, target);
	caster.AddStatus(std::make_unique<ContinueHeal>(continueRound, heal));
	caster.CoutSkill(name, heal, this);
}

int ContinuousHeal::CalculateSkillScore(Character& caster, Character& target)
{
	return 0;
}

void ContinuousHeal::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n恢复了";
	Render::RenderText(std::to_string(value), TextColor::LightGreen);
	std::cout << "点血量\n";
}

void OneTimeHeal::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n恢复了";
	Render::RenderText(std::to_string(value), TextColor::LightGreen);
	std::cout << "点血量\n";
}