#include "Character.h"
#include "BattleManager.h"
#include "Damage.h"
#include "HealSkill.h"
#include "SkillFactory.h"
#include <memory>

Character::Character(const std::string NameIn, const int HPIn,
							const int AttackIn, const int DefenseIn)
	: Name(NameIn), HP(HPIn),
		Attack(AttackIn),
		Defense(DefenseIn){}

void Character::TakeDamage(int damage) {
	HP -= damage;
}


bool Character::IsDead() {
	return HP <= 0;
}

CharacterInfo Character::GetInfo() {
	return {
		Name,
		HP,
		Attack,
		Defense
	};
}

void Character::SetHP(int hp) {
	HP = hp > 100 ? 100 : hp;
}

void Character::SetDefense(int defense) {
	Defense = defense;
}

void Character::InitSkill(Character& caster, Character& target)
{
	skills.push_back(std::make_unique<Damage>(
		"火球术", 1,
		SkillFactory::CreateFireBall
	));
	skills.push_back(std::make_unique<Damage>(
		"冰封j", 3,
		SkillFactory::CreateIceSword
	));
	skills.push_back(std::make_unique<OneTimeHeal>(
		"血量回复", 2,
		SkillFactory::CreateOneTimeHealHP
	));
	skills.push_back(std::make_unique<ContinuousHeal>(
		"持续回复", 4, 3,
		SkillFactory::CreateContinuousHealHP
	));
	skills.push_back(std::make_unique<DefenseUp>(
		"防御提升", 1,
		SkillFactory::CreateDefenseUp
	));
}
