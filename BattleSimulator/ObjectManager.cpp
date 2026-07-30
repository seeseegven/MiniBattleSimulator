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
	char act;
	for (auto& character : characters) {
		
		if (dynamic_cast<Player*>(character.get())) {
			std::cout << "请输入a进行攻击" << std::endl;
			std::cin >> act;
			while (act != 'a') {
				std::cout << "请输入a进行攻击" << std::endl;
				std::cin >> act;
			}
			std::unique_ptr<Skill> skill1 = std::make_unique<Damage>("火球术");
			//character->Attack(*characters[1], 20);
			skill1->Use(*character, *characters[1]);
			Render::WaitForDisplay(3000);
		}
		else {
			character->AttackOpponent(*characters[0], 15);
			std::cout << "敌人进行普攻，造成了";
			Render::RenderText("15", TextColor::Red);
			std::cout << "点伤害" << std::endl;
			Render::WaitForDisplay(1200);
		}
	}
}


void ObjectManager::CoutInfo() {
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}