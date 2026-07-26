#pragma once
#include <memory>
#include "ObjectManager.h"
#include "BattleManager.h"

enum class GameState
{
	Menu,
	Battle
};

class Game
{
public:
	Game(); //构造函数
	void Run(); //运行游戏
	
private:
	//std::unique_ptr<ObjectManager> manager; //对象管理器
	std::unique_ptr<BattleManager> battleManager; //战斗管理器
	bool isRunning; //游戏是否正在运行
	GameState CurrentState; //当前游戏状态	
	void Input(); //处理输入
	void EnterBattle(); //进入战斗
	void Update(); //更新游戏状态
	void Render(); //渲染游戏画面
};