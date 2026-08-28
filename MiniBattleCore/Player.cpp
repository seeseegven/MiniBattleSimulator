#include "Player.h"

Player::Player(std::string name, int hp) 
	: Character(name, hp) {}

void Player::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound)
{
}
