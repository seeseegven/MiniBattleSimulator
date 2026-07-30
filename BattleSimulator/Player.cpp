#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::AttackOpponent(Character& target, int harm) {
	target.TakeDamage(harm);
	cout << Name << "»Ó½£¹¥»÷" << endl;
}