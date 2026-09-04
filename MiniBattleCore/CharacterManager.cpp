#include "CharacterManager.h"
#include "Character.h"

void CharacterManager::AddCharacter(std::unique_ptr<Character> character)
{
	characters.push_back(std::move(character));
}

std::vector<std::unique_ptr<Character>>& CharacterManager::GetCharacters()
{
	return characters;
}

std::string CharacterManager::StringToSend(States states)
{
	if (states == States::init) {
		std::string str;
		for (auto& c : characters) {//要用引用啊，uniqueptr是独占的，不能复制
			auto [name, hp, attack, defense] = c->GetInfo();
			str += std::to_string(hp);
			str = str + "," + std::to_string(attack);
			str = str + "," + std::to_string(defense) + ",";
			str += ";";
		}
		str += '\n';
		return str;
	}
	else if (states == States::waitForBattle) {
		return "等待进入对局";
	}
}
