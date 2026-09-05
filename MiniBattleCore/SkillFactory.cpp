#include "SkillFactory.h"

int SkillFactory::CreateFireBall(Character& caster, Character& target)
{
	CharacterInfo casterInfo = caster.GetInfo();
	CharacterInfo targetInfo = target.GetInfo();
	return casterInfo.Attack
		* (1 - targetInfo.Defense / (static_cast<double>(targetInfo.Defense) + 200));
}

int SkillFactory::CreateIceSword(Character& caster, Character& target)
{
	CharacterInfo casterInfo = caster.GetInfo();
	CharacterInfo targetInfo = target.GetInfo();
	return casterInfo.Attack * 0.5;
}

int SkillFactory::CreateOneTimeHealHP(Character& caster, Character& target)
{
	return 30;
}

int SkillFactory::CreateDefenseUp(Character& caster, Character& target)
{
	return 10;
}

int SkillFactory::CreateContinuousHealHP(Character& caster, Character& target)
{
	return 12;
}
