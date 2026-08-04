#include "EnemyAI.h"
#include "Character.h"

SkillType EnemyAI::ChooseSkill(Character& self, Character& target) {
	CharacterInfo selfInfo = self.GetInfo();
	CharacterInfo targetInfo = target.GetInfo();
	if (selfInfo.HP < 30) {
		return SkillType::Heal;
	}
	else if (targetInfo.HP < 20) {
		return SkillType::Damage;
	}
	else {
		return SkillType::Damage;
	}
}