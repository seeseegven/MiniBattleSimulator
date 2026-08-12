#include "Player.h"
#include "Damage.h"
#include "HealSkill.h"
#include "Render.h"
#include <iostream>
#include <functional>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound) {
	std::string act;
	CoutSkillList(curRound);
	std::cin >> act;
	while (act.size() != 1 || act[0]<'1' || act[0]>'4' 
		|| skills[act[0]-'1']->GetRoundLeft() > curRound) {
		//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Render::ClearScreen();
		for (const auto& character : characters) {
			std::cout << *character << std::endl;
		}
		CoutSkillList(curRound);
		std::cin >> act;
	}
	skills[act[0] - '1']->Use(*characters[0], *characters[1]);
	skills[act[0] - '1']->SetRoundLeft(curRound);
	Render::WaitForDisplay(3000);
}

void Player::CoutSkillList(int curRound) {
	std::cout << "请选择你要施放的技能\n";
	for (int i = 0; i < skills.size(); i++) {
		std::cout << i + 1 << "." << skills[i]->GetName();
		skills[i]->PrintDetail(curRound);
	}
}

void Player::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}