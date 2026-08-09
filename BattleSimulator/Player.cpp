#include "Player.h"
#include "Damage.h"
#include "HealSkill.h"
#include <iostream>
#include <functional>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	std::string act;
	CoutSkillList();
	std::cin >> act;
	while (act.size()!=1 || act[0]<'1' || act[0]>'4') {
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Render::ClearScreen();
		for (const auto& character : characters) {
			std::cout << *character << std::endl;
		}
		CoutSkillList();
		std::cin >> act;
	}
	std::unique_ptr<Skill> skill1, skill2;
	if (act[0] == '1') {
		skills[0]->Use(*characters[0], *characters[1]);
	}else if (act[0] == '2') {
		skills[1]->Use(*characters[0], *characters[1]);
	}else if (act[0] == '3') {
		skills[2]->Use(*characters[0], *characters[1]);
	}
	else {
		std::unique_ptr<HealSkill> defenseUpSkill = std::make_unique<DefenseUp>("防御增加");
		defenseUpSkill->Effect(*characters[0]);
	}
	Render::WaitForDisplay(3000);
}

void Player::CoutSkillList() {
	std::cout << "请选择你要施放的技能\n";
	for (int i = 0; i < skills.size(); i++) {
		std::cout << i + 1 << "." << skills[i]->GetName() << std::endl;
	}
}

void Player::CoutSkill(const std::string& s, int value) {
	std::cout << "玩家使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}