#pragma once
#include <string>

class Character;

class Skill {
public:
	Skill(const std::string& s, const int round = 0) : name(s), coolDown(round) {}
	virtual void Use(Character& caster, Character& target) = 0;
	virtual ~Skill() = default;
	virtual std::string GetName();
	virtual int CalculateSkillScore(Character& caster, Character& target) = 0;
	int GetWhichRoundCanUse() const;
	virtual void SetWhichRoundCanUse(int curRound);
	virtual void PrintDetail(int curRound);
	virtual std::string SkillEffect(const std::string& s, int value) = 0;
protected:
	std::string name;
	int whichRoundCanUse = 0;
	int coolDown;
};
