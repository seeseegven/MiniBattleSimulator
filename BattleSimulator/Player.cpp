#include "Player.h"
#include "Damage.h"
#include "HealSkill.h"
#include "Render.h"
#include <iostream>
#include <functional>


Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound) {
	std::string act;
	CoutSkillList(curRound);
	COORD info = Render::GetCursorPosition();
    std::cin >> act;
	while (act.size() != 1 || act[0]<'1' || act[0]-'1'>skills.size() //妈的老是忘记-'1'转成整数。。。
		|| skills[act[0]-'1']->GetRoundLeft() > curRound) {
		Render::SetCursorPosition(0, info.Y);
		std::cout << "\033[2K"; 
		std::cin >> act;
	}
	skills[act[0] - '1']->Use(*characters[0], *characters[1]);
	skills[act[0] - '1']->SetRoundLeft(curRound);
	Render::WaitForDisplay(1200);
}

void Player::CoutSkillList(int curRound) {
	std::cout << "请选择你要施放的技能\n";
	for (int i = 0; i < skills.size(); i++) {
		std::cout << i + 1 << "." << skills[i]->GetName();
		skills[i]->PrintDetail(curRound);
	}
}

void Player::PrintCurrentRound(int curRound) {
	Render::RenderText("当前为第 ", TextColor::White);
	Render::RenderText(std::to_string(curRound + 1), TextColor::LightMagenta);
	Render::RenderText(" 回合\n", TextColor::White);
}

void Player::CoutSkill(const std::string& s, int value, Skill* skill) {
	std::cout << "玩家使用 ";
	skill->SkillEffect(s, value);
}