#include "HealSkill.h"
#include "Character.h"
#include "SkillFactory.h"
#include "Render.h"
#include "EffectStatus.h"
#include <iostream>
#include <memory>

void OneTimeHeal::Use(Character& caster, Character& target)
{
	CharacterInfo casterInfo = caster.GetInfo();
	int heal = SkillFactory::CreateOneTimeHealHP(caster, target);
	caster.SetHP(casterInfo.HP + heal);
	caster.CoutSkill(name, heal, this);
}

int OneTimeHeal::CalculateSkillScore(Character& caster, Character& target)
{
	return 100 - caster.GetInfo().HP;
}

void DefenseUp::Use(Character& caster, Character& target)
{
	auto info = caster.GetInfo();
	int defense = SkillFactory::CreateDefenseUp(caster, target);
	caster.SetDefense(info.Defense + defense);
	caster.CoutSkill(name, defense, this);
}

int DefenseUp::CalculateSkillScore(Character& caster, Character& target)
{
	return 0;
}

std::string DefenseUp::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n\u589E\u52A0\u4E86";
	Render::RenderText(std::to_string(value), TextColor::LightBlue);
	std::cout << "\u70B9\u9632\u5FA1\n";
	return s + ",\n\u589E\u52A0\u4E86" + std::to_string(value) + "\u70B9\u9632\u5FA1\n";
}

void ContinuousHeal::Use(Character& caster, Character& target)
{
	CharacterInfo casterInfo = caster.GetInfo();
	int heal = SkillFactory::CreateContinuousHealHP(caster, target);
	caster.AddStatus(std::make_unique<ContinueHeal>(continueRound, heal));
	caster.CoutSkill(name, heal, this);
}

int ContinuousHeal::CalculateSkillScore(Character& caster, Character& target)
{
	return 0;
}

std::string ContinuousHeal::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n\u6062\u590D\u4E86";
	Render::RenderText(std::to_string(value), TextColor::LightGreen);
	std::cout << "\u70B9\u8840\u91CF\n";
	return s + ",\n\u6062\u590D\u4E86" + std::to_string(value) + "\u70B9\u8840\u91CF\n";
}

std::string OneTimeHeal::SkillEffect(const std::string& s, int value)
{
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n\u6062\u590D\u4E86";
	Render::RenderText(std::to_string(value), TextColor::LightGreen);
	std::cout << "\u70B9\u8840\u91CF\n";
	return s + ",\n\u6062\u590D\u4E86" + std::to_string(value) + "\u70B9\u8840\u91CF\n";
}
