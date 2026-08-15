#pragma once

class Character;

class EffectStatus {
public:
	EffectStatus(int, int);
	bool IsExpired();
	virtual void StatusFunction(Character&) = 0;
	int GetRoundLeft() const; //获取技能效果剩余回合数
protected:
	int roundLeft;
	int value;
};

class ContinueHeal : public EffectStatus{
public:
	ContinueHeal(int, int);
	void StatusFunction(Character&) override;
};