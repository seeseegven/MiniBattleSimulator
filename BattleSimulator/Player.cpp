#include "Player.h"
#include "Damage.h"
#include "HealSkill.h"
#include <iostream>
#include <functional>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	int act;
	CoutSkillList();
	std::cin >> act;
	while (act <1||act >4) {
		Render::ClearScreen();
		for (const auto& character : characters) {
			std::cout << *character << std::endl;
		}
		CoutSkillList();
		std::cin >> act;
	}
	std::unique_ptr<Skill> skill1, skill2;
	if (act == 1) {
		skill1 = std::make_unique<Damage>(
			"火球术",
			[](Character& caster, Character& target) {
				CharacterInfo CasterInfo = caster.GetInfo();
				CharacterInfo TargetInfo = target.GetInfo();
				return CasterInfo.Attack * 1.5 - TargetInfo.Defense * 0.3;
			}
		);
		skill1->Use(*characters[0], *characters[1]);
	}else if (act == 2) {
		skill2 = std::make_unique<Damage>(
			"",
			[](Character& caster, Character& target) {
				CharacterInfo CasterInfo = caster.GetInfo();
				CharacterInfo TargetInfo = target.GetInfo();
				return CasterInfo.Attack * 1.2;
			}
		);
		skill2->Use(*characters[0], *characters[1]);
	}else if (act == 3) {
		std::unique_ptr<HealSkill> healSkill = std::make_unique<Heal>("血量回复");
		healSkill->Effect(*characters[0]);
	}
	else {
		std::unique_ptr<HealSkill> defenseUpSkill = std::make_unique<DefenseUp>("防御增加");
		defenseUpSkill->Effect(*characters[0]);
	}
	Render::WaitForDisplay(3000);
}

void Player::CoutSkillList() {
	std::cout << "请选择你要施放的技能\n";
	std::cout << "1.火球术\n";
	std::cout << "2.冰封剑\n";
	std::cout << "3.血量回复\n";
	std::cout << "4.防御增加\n";
}