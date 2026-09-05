#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void CharacterManager::Action(int curRound)
{
	static_cast<Player*>(characters[0].get())->RoundBehavior(characters, curRound);
	static_cast<Enemy*>(characters[1].get())->RoundBehavior(characters, curRound);
}

void CharacterManager::CoutInfo()
{
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}
