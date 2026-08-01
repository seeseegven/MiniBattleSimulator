#include "Player.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::AttackOpponent(Character& target, int harm) {
	target.TakeDamage(harm);
}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	char act;
	CoutSkillList();
	std::cin >> act;
	while (act - '0'<1||act-'0'>4) {
		Render::ClearScreen();
		for (const auto& character : characters) {
			std::cout << *character << std::endl;
		}
		CoutSkillList();
		std::cin >> act;
	}
	std::unique_ptr<Skill> skill1;
	if (act == '1') {
		skill1 = std::make_unique<Damage>("火球术", 1.1);
	}
	else if (act == '2') {
		skill1 = std::make_unique<Damage>("冰封剑", 2);
	}
	skill1->Use(*characters[0], *characters[1]);
	Render::WaitForDisplay(3000);
}

void Player::CoutSkillList() {
	std::cout << "请选择你要施放的技能\n";
	std::cout << "1.火球术\n";
	std::cout << "2.冰封剑\n";
	std::cout << "3.血量回复\n";
	std::cout << "4.防御增加\n";
}