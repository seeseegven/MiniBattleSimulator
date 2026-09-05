#include "CharacterManager.h"
#include "Character.h"
#include <iostream>

void CharacterManager::AddCharacter(std::unique_ptr<Character> character)
{
	characters.push_back(std::move(character));
}

std::vector<std::unique_ptr<Character>>& CharacterManager::GetCharacters()
{
	return characters;
}

void CharacterManager::Action(int curRound)
{
	for (auto& character : characters) {
		character->RoundBehavior(characters, curRound);
	}
}

void CharacterManager::CoutInfo()
{
	for (const auto& character : characters) {
		std::cout << *character << std::endl;
	}
}

std::string CharacterManager::StringToSend(const std::string& actionMessage)
{
	std::string str;
	for (auto& c : characters) {//要用引用啊，uniqueptr是独占的，不能复制
		auto [name, hp, attack, defense] = c->GetInfo();
		str += std::to_string(hp);
		str = str + "," + std::to_string(attack);
		str = str + "," + std::to_string(defense) + ",";
		str += ";";
	}
	str += '\n';
	str = "Success|" + str;
	str += actionMessage;
	return str;
}
