#include "Enemy.h"
#include "Damage.h"
#include "HealSkill.h"
#include <iostream>

using namespace std;

Enemy::Enemy(std::string name, int hp)
	: Character(name, hp) {
}


void Enemy::RoundBehavior(std::vector<std::unique_ptr<Character>>& characters) {
	SkillType type = ai.ChooseSkill(*this, *characters[0]);
	std::unique_ptr<Skill> skill;
	switch (type)
	{
	case SkillType::Damage:
		skill = std::make_unique<Damage>(
			"敌人攻击",
			[](Character& caster, Character& target) {
				CharacterInfo CasterInfo = caster.GetInfo();
				CharacterInfo TargetInfo = target.GetInfo();
				return CasterInfo.Attack * 1.0 - TargetInfo.Defense * 0.2;
			}
		);
		break;
	case SkillType::Heal:
		skill = std::make_unique<Heal>("敌人回血");
		break;
	}
	skill->Use(*characters[1], *characters[0]);
	/*characters[0]->TakeDamage(15);
	std::cout << "敌人进行普攻，造成了";
	Render::RenderText("15", TextColor::Red);
	std::cout << "点伤害" << std::endl;*/
	Render::WaitForDisplay(1200);
}

void Enemy::CoutSkill(const std::string& s, int value) {
	std::cout << "敌人使用 ";
	Render::RenderText(s, TextColor::LightCyan);
	std::cout << ",\n造成了";
	Render::RenderText(std::to_string(value), TextColor::Red);
	std::cout << "点伤害\n";
}