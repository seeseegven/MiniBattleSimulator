#include "SkillFactory.h"

int SkillFactory::CreateFireBall(Character& caster, Character& target)
{
	CharacterInfo CasterInfo = caster.GetInfo();
	CharacterInfo TargetInfo = target.GetInfo();
	return CasterInfo.Attack * 1.5 - TargetInfo.Defense * 0.3;
}

int SkillFactory::CreateIceSword(Character& caster, Character& target)
{
	CharacterInfo CasterInfo = caster.GetInfo();
	CharacterInfo TargetInfo = target.GetInfo();
	return CasterInfo.Attack * 1.2;
}

int SkillFactory::CreateHealHP(Character& caster, Character& target)
{
	return 30;
}

int SkillFactory::CreateDefenseUp(Character& caster, Character& target)
{
	return 10;
}
