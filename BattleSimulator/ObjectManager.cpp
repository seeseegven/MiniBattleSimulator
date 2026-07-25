#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"

void ObjectManager::AddCharacter(std::unique_ptr<Character> character) {
	characters.push_back(std::move(character));
	//unique_ptr是独占的，不能复制只能移动，不然会有
}

void ObjectManager::Action() {
	for (auto& character : characters) {
		if (dynamic_cast<Player*>(character.get())) {
			character->Attack(*characters[1]);
		}
		else {
			character->Attack(*characters[0]);
		}
	}
}

void ObjectManager::PrintAll() {
	for (const auto& character : characters) {
		character->Print();
	}
}