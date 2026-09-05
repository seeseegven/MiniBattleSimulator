#include "Character.h"
#include "Damage.h"
#include "HealSkill.h"
#include "SkillFactory.h"
#include "EffectStatus.h"

Character::Character(const std::string NameIn, const int HPIn,
	const int AttackIn, const int DefenseIn)
	: Name(NameIn), HP(HPIn),
	Attack(AttackIn),
	Defense(DefenseIn) {
}

void Character::TakeDamage(int damage) {
	HP -= damage;
}

bool Character::IsDead() {
	return HP <= 0;
}

Character::~Character() = default;

CharacterInfo Character::GetInfo()
{
	return {
		Name,
		HP,
		Attack,
		Defense
	};
}

void Character::SetHP(int hp)
{
	HP = hp > 100 ? 100 : hp;
}

void Character::SetDefense(int defense)
{
	Defense = defense;
}

void Character::InitSkill(Character& caster, Character& target)
{
	skills.push_back(std::make_unique<Damage>(
		"\u706B\u7403\u672F", 1,
		SkillFactory::CreateFireBall
	));
	skills.push_back(std::make_unique<Damage>(
		"\u51B0\u5C01j", 3,
		SkillFactory::CreateIceSword
	));
	skills.push_back(std::make_unique<OneTimeHeal>(
		"\u8840\u91CF\u56DE\u590D", 2,
		SkillFactory::CreateOneTimeHealHP
	));
	skills.push_back(std::make_unique<ContinuousHeal>(
		"\u6301\u7EED\u56DE\u590D", 4, 3,
		SkillFactory::CreateContinuousHealHP
	));
	skills.push_back(std::make_unique<DefenseUp>(
		"\u9632\u5FA1\u63D0\u5347", 1,
		SkillFactory::CreateDefenseUp
	));
}

void Character::AddStatus(std::unique_ptr<EffectStatus>&& status)
{
	Statuses.push_back(std::move(status));
}

bool Character::UseSkill(size_t skillIndex, Character& target, int curRound)
{
	if (skillIndex >= skills.size()
		|| skills[skillIndex]->GetWhichRoundCanUse() > curRound) {
		return false;
	}

	skills[skillIndex]->Use(*this, target);
	skills[skillIndex]->SetWhichRoundCanUse(curRound);

	for (auto it = Statuses.begin(); it != Statuses.end();) {
		if (!((*it)->IsExpired())) {
			(*it)->StatusFunction(*this);
			it++;
		}
		else {
			it = Statuses.erase(it);
		}
	}
	return true;
}

const std::string& Character::GetLastActionMessage() const
{
	return lastActionMessage;
}

void Character::RecordActionMessage(const std::string& effectMessage)
{
	lastActionMessage = Name + "\u4F7F\u7528 " + effectMessage;
}
