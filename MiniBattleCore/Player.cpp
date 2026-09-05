#include "Player.h"
#include "Skill.h"
#include "Render.h"
#include <iostream>

Player::Player(std::string name, int hp) 
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound)
{
	std::string act;
	CoutSkillList(curRound);
	COORD info = Render::GetCursorPosition();
	std::cin >> act;
	while (act.size() != 1 || act[0] < '1'
		|| static_cast<size_t>(act[0] - '1') >= skills.size()
		|| skills[act[0] - '1']->GetWhichRoundCanUse() > curRound) {
		Render::SetCursorPosition(0, info.Y);
		std::cout << "\033[2K";
		std::cin >> act;
	}
	UseSkill(act[0] - '1', *characters[1], curRound);
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
	Render::RenderText("\u5F53\u524D\u4E3A\u7B2C ", TextColor::White);
	Render::RenderText(std::to_string(curRound + 1), TextColor::LightMagenta);
	Render::RenderText(" \u56DE\u5408\n", TextColor::White);
}

void Player::CoutSkill(const std::string& s, int value, Skill* skill)
{
	std::cout << "\u73A9\u5BB6\u4F7F\u7528 ";
	skill->SkillEffect(s, value);
}

void Player::CoutSkill(const std::string& s, Skill* skill)
{
}
