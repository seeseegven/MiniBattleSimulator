#pragma once
#include <string>
#include <iostream>
#include <vector>

class Skill;

struct CharacterInfo {
	std::string Name;
	int HP;
	int Attack;
	int Defense;
};

class Character
{
public:
	Character(const std::string NameIn, const int HPIn=100,
		const int AttackIn=30, const int DefenseIn=100);
	friend std::ostream& operator<<(std::ostream& os, Character& character);
	void TakeDamage(int demage);
	bool IsDead();
	virtual ~Character() = default;
	CharacterInfo GetInfo();
	void SetHP(int hp);
	void SetDefense(int defense);
	virtual void CoutSkill(const std::string& s, int value) = 0;
	virtual void RoundBehavior(std::vector<std::unique_ptr<Character>>& characters, int curRound) = 0;
	void InitSkill(Character& caster, Character& target);
	const auto& GetSkills() { return skills; };
protected:
	int Attack;
	int Defense;
	std::string Name;
	int HP;//到时候调下顺序
	std::vector<std::unique_ptr<Skill>> skills;
};