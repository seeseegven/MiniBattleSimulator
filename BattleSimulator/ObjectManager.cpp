#include "ObjectManager.h"

void ObjectManager::AddCharacter(std::unique_ptr<Character> character) {
	characters.push_back(std::move(character));
	//unique_ptr是独占的，不能复制只能移动，不然会有
}

void ObjectManager::Update() {
	for (auto& character : characters) {
		character->Attack();
	}
}