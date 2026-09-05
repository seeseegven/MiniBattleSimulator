#include "EffectStatus.h"
#include "Character.h"

EffectStatus::EffectStatus(int round, int value)
	: roundLeft(round), value(value)
{
}

bool EffectStatus::IsExpired()
{
	return roundLeft <= 0;
}

int EffectStatus::GetRoundLeft() const
{
	return roundLeft;
}

ContinueHeal::ContinueHeal(int round, int value)
	: EffectStatus(round, value)
{
}

void ContinueHeal::StatusFunction(Character& caster)
{
	caster.SetHP(caster.GetInfo().HP + value);
	roundLeft--;
}
