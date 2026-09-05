#include "Skill.h"
#include "Render.h"

void Skill::PrintDetail(int curRound)
{
	int roundDiff = whichRoundCanUse - curRound >= 0
		? whichRoundCanUse - curRound : 0;
	Render::RenderText("      " + std::to_string(roundDiff), TextColor::LightBlue);
	Render::RenderText(" \u56DE\u5408\u540E\u53EF\u7528\n", TextColor::White);
}
