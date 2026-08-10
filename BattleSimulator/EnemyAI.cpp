#include "EnemyAI.h"
#include "Character.h"
#include "SkillFactory.h"
#include "Skill.h"

int EnemyAI::ChooseSkill(Character& caster, Character& target) {
	//分数计算等于造成伤害/回血 + 扣除血量；
	CharacterInfo casterInfo = caster.GetInfo();
	CharacterInfo targetInfo = target.GetInfo();
	const auto& skills = caster.GetSkills();
	int maxScore = skills[0]->CalculateSkillScore(caster, target);
	int index = 0;
	for (int i = 1; i < skills.size();i++ ) {
		if (skills[i]->CalculateSkillScore(caster, target) > maxScore) {
			maxScore = skills[i]->CalculateSkillScore(caster, target);
			index = i;
		}
	}
	return index;
}