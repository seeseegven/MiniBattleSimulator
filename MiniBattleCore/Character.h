#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>


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
	//void TakeDamage(int demage);
	bool IsDead();
	virtual ~Character()=default;
	CharacterInfo GetInfo();
	void SetHP(int hp);
	void SetDefense(int defense);
	//virtual void CoutSkill(const std::string& s, int value, Skill* skill) = 0;
	//virtual void CoutSkill(const std::string& s, Skill* skill) = 0;
	virtual void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound) = 0;
	//void InitSkill(Character& caster, Character& target);
	//const auto& GetSkills() { return skills; };
	//void AddStatus(std::unique_ptr<EffectStatus>&& status);
protected:
	int Attack;
	int Defense;
	std::string Name;
	int HP;//到时候调下顺序
	//std::vector<std::unique_ptr<Skill>> skills;
	//std::vector<std::unique_ptr<EffectStatus>> Statuses;
};