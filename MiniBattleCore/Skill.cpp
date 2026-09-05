#include "Skill.h"

std::string Skill::GetName()
{
	return name;
}

int Skill::GetWhichRoundCanUse() const
{
	return whichRoundCanUse;
}

void Skill::SetWhichRoundCanUse(int curRound)
{
	whichRoundCanUse = coolDown + curRound;
}
