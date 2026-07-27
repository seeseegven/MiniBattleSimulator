#include "Attribution.h"

Attribution::Attribution(int attackIn, int defenseIn)
	: attack(attackIn), defense(defenseIn) {
}

int Attribution::GetAttack() const {
	return attack;
}

int Attribution::GetDefense() const {
	return defense;
}
