#include "Skill.h"
#include "Render.h"

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

void Skill::PrintDetail(int curRound)
{
	int roundDiff = whichRoundCanUse - curRound >= 0
		? whichRoundCanUse - curRound : 0;
	Render::RenderText("      "+std::to_string(roundDiff), TextColor::LightBlue);
	Render::RenderText(" 回合后可用\n", TextColor::White);
}
