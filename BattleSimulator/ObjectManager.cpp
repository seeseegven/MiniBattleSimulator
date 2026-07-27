#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

void ObjectManager::AddCharacter(std::unique_ptr<Character> character) {
	characters.push_back(std::move(character));
	//unique_ptr是独占的，不能复制只能移动，不然会有
}

void ObjectManager::Action() {
	char act;
	for (auto& character : characters) {
		std::cout << "请输入a进行攻击" << std::endl;
		if (dynamic_cast<Player*>(character.get())) {
			std::cin >> act;
			while (act != 'a') {
				std::cout << "请输入a进行攻击" << std::endl;
				std::cin >> act;
			}
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

void ObjectManager::CoutInfo() {
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}