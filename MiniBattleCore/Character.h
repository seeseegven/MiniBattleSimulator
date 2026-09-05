#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>

class Skill;
class EffectStatus;

struct CharacterInfo {
	std::string Name;
	int HP;
	int Attack;
	int Defense;
};

enum class Status : unsigned {
	None = 0,
	ContinueHeal = 1 << 0
};

class Character
{
public:
	Character(const std::string NameIn, const int HPIn = 100,
		const int AttackIn = 30, const int DefenseIn = 100);
	friend std::ostream& operator<<(std::ostream& os, Character& character);
	void TakeDamage(int damage);
	bool IsDead();
	virtual ~Character();
	CharacterInfo GetInfo();
	void SetHP(int hp);
	void SetDefense(int defense);
	virtual void CoutSkill(const std::string& s, int value, Skill* skill) = 0;
	virtual void CoutSkill(const std::string& s, Skill* skill) = 0;
	void InitSkill(Character& caster, Character& target);
	const auto& GetSkills() const { return skills; };
	void AddStatus(std::unique_ptr<EffectStatus>&& status);
	bool UseSkill(size_t skillIndex, Character& target, int curRound);
	const std::string& GetLastActionMessage() const;
protected:
	void RecordActionMessage(const std::string& effectMessage);
	int Attack;
	int Defense;
	std::string Name;
	int HP;//到时候调下顺序
	std::vector<std::unique_ptr<Skill>> skills;
	std::vector<std::unique_ptr<EffectStatus>> Statuses;
	std::string lastActionMessage;
};
