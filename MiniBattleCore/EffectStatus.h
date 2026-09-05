#pragma once

class Character;

class EffectStatus {
public:
	EffectStatus(int round, int value);
	bool IsExpired();
	virtual void StatusFunction(Character& character) = 0;
	int GetRoundLeft() const;
protected:
	int roundLeft;
	int value;
};

class ContinueHeal : public EffectStatus {
public:
	ContinueHeal(int round, int value);
	void StatusFunction(Character& character) override;
};
