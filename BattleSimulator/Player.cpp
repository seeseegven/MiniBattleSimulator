#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(std::string name, int hp)
	: Character(name, hp) {}

void Player::Attack() {
	cout << "Hero»Ó½£¹¥»÷" << endl;
}