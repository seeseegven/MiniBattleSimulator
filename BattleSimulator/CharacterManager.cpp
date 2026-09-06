#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void CharacterManager::Action(int curRound, bool& isRunning)
{
	static_cast<Player*>(characters[0].get())->RoundBehavior(characters, curRound, isRunning);
	if (!isRunning) return;
	static_cast<Enemy*>(characters[1].get())->RoundBehavior(characters, curRound);
}

void CharacterManager::CoutInfo()
{
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}
