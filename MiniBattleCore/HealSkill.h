#pragma once
#include "Skill.h"
#include <functional>

class OneTimeHeal : public Skill {
public:
	OneTimeHeal(const std::string& s, const int& round,
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Healfunc(func) {}
	~OneTimeHeal() override = default;
	void Use(Character& caster, Character& target) override;
	int CalculateSkillScore(Character& caster, Character& target) override;
	std::string SkillEffect(const std::string& s, int value) override;
private:
	std::function<int(Character&, Character&)> Healfunc;
};

class DefenseUp : public Skill {
public:
	DefenseUp(const std::string& s, const int& round,
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Defensefunc(func) {}
	~DefenseUp() override = default;
	void Use(Character& caster, Character& target) override;
	int CalculateSkillScore(Character& caster, Character& target) override;
	std::string SkillEffect(const std::string& s, int value) override;
private:
	std::function<int(Character&, Character&)> Defensefunc;
};

class ContinuousHeal : public Skill {
public:
	ContinuousHeal(const std::string& s, const int& round, int continueRound,
		std::function<int(Character&, Character&)> func)
		: Skill(s, round), Healfunc(func), continueRound(continueRound) {}
	~ContinuousHeal() override = default;
	void Use(Character& caster, Character& target) override;
	int CalculateSkillScore(Character& caster, Character& target) override;
	std::string SkillEffect(const std::string& s, int value) override;
private:
	int continueRound;
	std::function<int(Character&, Character&)> Healfunc;
};
