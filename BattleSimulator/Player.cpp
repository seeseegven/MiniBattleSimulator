#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::Attack(Character& target) {
	target.TakeDamage(20);
	cout << Name << "»Ó½£¹¥»÷" << endl;
}