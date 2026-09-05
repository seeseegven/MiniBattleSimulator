#include "Enemy.h"
#include "Skill.h"
#include "Render.h"

void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound)
{
	int index = ai.ChooseSkill(*this, *characters[0]);
	skills[index]->Use(*this, *characters[0]);
	Render::DisplayActionMessage(GetLastActionMessage());
	Render::WaitForDisplay(1200);
}
