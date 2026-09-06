#include "Player.h"
#include "Skill.h"
#include "Render.h"
#include <iostream>

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound, bool& isRunning)
{
	std::string act;
	CoutSkillList(curRound);
	COORD info = Render::GetCursorPosition();
	std::cin >> act;
	if (act == "z") {
		isRunning = false;
		return;
	}
	while (act.size() != 1 || act[0] < '1'
		|| static_cast<size_t>(act[0] - '1') >= skills.size()
		|| skills[act[0] - '1']->GetWhichRoundCanUse() > curRound) {
		Render::SetCursorPosition(0, info.Y);
		std::cout << "\033[2K";//清空该行，不移动光标
		std::cin >> act;
	}
	UseSkill(act[0] - '1', *characters[1], curRound);
	Render::DisplayActionMessage(GetLastActionMessage());
	Render::WaitForDisplay(1200);
}

void Player::CoutSkillList(int curRound)
{
	std::cout << "\u8BF7\u9009\u62E9\u4F60\u8981\u65BD\u653E\u7684\u6280\u80FD\n";
	for (size_t i = 0; i < skills.size(); i++) {
		std::cout << i + 1 << "." << skills[i]->GetName();
		skills[i]->PrintDetail(curRound);
	}
}

void Player::PrintCurrentRound(int curRound)
{
	Render::DisplayCurrentRound(curRound + 1);
}
