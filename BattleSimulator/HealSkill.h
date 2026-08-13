#pragma once
#include <functional>
#include "Skill.h"

class OneTimeHeal : public Skill {
public:
	OneTimeHeal(const std::string& s, const int& round, 
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Healfunc(func) {
	}
	~OneTimeHeal() override = default;
	virtual void Use(Character& caster, Character& target);
	int CalculateSkillScore(Character& caster, Character& target) override;
	void SkillEffect(const std::string& s, int value);
private:
	std::function<int(Character&, Character&)> Healfunc;
};

class DefenseUp : public Skill {
public:
	DefenseUp(const std::string& s, const int& round,
		std::function<int(Character&, Character&)> func) 
		: Skill(s, round) , Defensefunc(func){}
	~DefenseUp() override = default;
	virtual void Use(Character& caster, Character& target);
	int CalculateSkillScore(Character& caster, Character& target) override;
	void SkillEffect(const std::string& s, int value) override;
private:
	std::function<int(Character&, Character&)> Defensefunc;
};

class ContinuousHeal : public Skill {
public:
	ContinuousHeal(const std::string& s, const int& round, int continueRound,
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Healfunc(func), roundLeft(continueRound){
	}
	~ContinuousHeal() override = default;
	virtual void Use(Character& caster, Character& target);
	int CalculateSkillScore(Character& caster, Character& target) override;
	void SkillEffect(const std::string& s, int value) override;
private:
	int roundLeft;//技能效果持续时间
	std::function<int(Character&, Character&)> Healfunc;
};