#pragma once

class Attribution {
public:
	Attribution(int attackIn=100, int defenseIn=100);
	int GetAttack() const;
	int GetDefense() const;
private:
	int attack;
	int defense;

};