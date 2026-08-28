#pragma once
#include <vector>
#include <memory>
#include "Character.h"
class CharacterManager
{
public:
	void AddCharacter(std::unique_ptr<Character> character);
	//void Action(int curRound);
	std::vector<std::unique_ptr<Character>>& GetCharacters();
	std::string  StringToSend();
private:
	std::vector<std::unique_ptr<Character>> characters;
};