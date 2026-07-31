#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Render.h"
#include "Damage.h"
#include <iostream>

void ObjectManager::AddCharacter(std::unique_ptr<Character> character) {
	characters.push_back(std::move(character));
	//unique_ptr是独占的，不能复制只能移动，不然会有
}

void ObjectManager::Action() {
	for (auto& character : characters) {
			character->RoundBehavior(characters);
	}
}


void ObjectManager::CoutInfo() {
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}