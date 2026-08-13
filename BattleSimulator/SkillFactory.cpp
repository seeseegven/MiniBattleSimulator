#include "SkillFactory.h"

int SkillFactory::CreateFireBall(Character& caster, Character& target)
{
	CharacterInfo CasterInfo = caster.GetInfo();
	CharacterInfo TargetInfo = target.GetInfo();
	return CasterInfo.Attack * (1-TargetInfo.Defense / (TargetInfo.Defense+100));
}

int SkillFactory::CreateIceSword(Character& caster, Character& target)
{
	CharacterInfo CasterInfo = caster.GetInfo();
	CharacterInfo TargetInfo = target.GetInfo();
	return CasterInfo.Attack * 1.5;
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
