#include "Player.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::AttackOpponent(Character& target, int harm) {
	target.TakeDamage(harm);
	cout << Name << "»Ó½£¹¥»÷" << endl;
}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	char act;
	std::cout << "ÇëÊäÈëa½øÐÐ¹¥»÷" << std::endl;
	std::cin >> act;
	while (act != 'a') {
		std::cout << "ÇëÊäÈëa½øÐÐ¹¥»÷" << std::endl;
		std::cin >> act;
	}
	std::unique_ptr<Skill> skill1 = std::make_unique<Damage>("»ðÇòÊõ");
	skill1->Use(*characters[0], *characters[1]);
	Render::WaitForDisplay(3000);
}