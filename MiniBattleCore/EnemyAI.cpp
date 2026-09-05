#include "EnemyAI.h"
#include "Character.h"
#include "Skill.h"

int EnemyAI::ChooseSkill(Character& caster, Character& target)
{
	const auto& skills = caster.GetSkills();
	int maxScore = skills[0]->CalculateSkillScore(caster, target);
	int index = 0;
	for (size_t i = 1; i < skills.size(); i++) {
		if (skills[i]->CalculateSkillScore(caster, target) > maxScore) {
			maxScore = skills[i]->CalculateSkillScore(caster, target);
			index = static_cast<int>(i);
		}
	}
	return index;
}
