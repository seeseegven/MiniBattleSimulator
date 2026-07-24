#pragma once
#include <vector>
#include <memory>

#include "Character.h"

class ObjectManager 
{
public:
	void AddCharacter(std::unique_ptr<Character> character);

	void Update();
private:
	std::vector<std::unique_ptr<Character>> characters;
};