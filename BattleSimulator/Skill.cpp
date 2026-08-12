#include "Skill.h"

std::string Skill::GetName()
{
	return name;
}

int Skill::GetRoundLeft() const{
	return whichRoundCanUse;
}

void Skill::SetRoundLeft(int curRound)
{
	whichRoundCanUse = coolDown + curRound;
}