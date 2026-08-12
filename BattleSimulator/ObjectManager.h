#pragma once
#include <vector>
#include <memory>

//#include "Character.h"
class Character;
class ObjectManager 
{
public:
	void AddCharacter(std::unique_ptr<Character> character);
	void CoutInfo();
	void Action(int curRound);
	std::vector<std::unique_ptr<Character>>& GetCharacters();
private:
	std::vector<std::unique_ptr<Character>> characters;
};