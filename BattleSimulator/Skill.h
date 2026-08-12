#pragma once
#include <string>

class Character;

class Skill {
public:
	Skill(const std::string& s, const int round=0) :name(s), coolDown(round) {}
	virtual void Use(Character& caster, Character& target)=0;
	virtual ~Skill()=default;
	virtual std::string GetName();
	virtual int CalculateSkillScore(Character& caster, Character& target)=0;
	int GetRoundLeft() const;//获取哪个回合才能使用该技能
	virtual void SetRoundLeft(int curRound);//设置哪个回合才能使用该技能
	virtual void PrintDetail(int curRound);
protected:
	std::string name;
	int whichRoundCanUse = 0;
	int coolDown;
};