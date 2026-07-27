#include "Game.h"
#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Enemy.h"
#include "ObjectManager.h"

using namespace std;

Game::Game() : isRunning(true) {
	CurrentState = GameState::Menu;
}

void Game::Run()
{
	cout
		<< "=====菜单=====\n"
		<< "b.开始游戏\n"
		<< "q.退出\n";
	while (isRunning) {
		Input();
		if (Game::isRunning == false) {
			cout << "已退出" << endl;
			break;
		}else if (CurrentState==GameState::Battle) {
			ClearScreen();
			cout << "进入战斗   " << "z退出" << endl;
			CurrentState = GameState::Battle;
			battleManager = std::make_unique<BattleManager>();
			//这里忘记初始化了，battlemanager没有实例化，后续指针赋值给player时找不到对象，报this为nullptr的错。
			EnterBattle();
			CurrentState = GameState::Menu;
		}
		Update();
		ClearScreen();
		Render();
	}
}

void Game::Input()
{
	//处理输入的逻辑
	char command;
	cout << "请输入指令，q退出\n";
	cin >> command;

	if (command == 'q') {
		isRunning = false;
	}
	else if (command == 'b' && CurrentState!=GameState::Battle) {
		CurrentState = GameState::Battle;
	}
	else if (command == 'z' && CurrentState == GameState::Battle) {
		CurrentState = GameState::Menu;
	}
}

void Game::Update()
{
	// 更新游戏状态的逻辑
	if (CurrentState == GameState::Battle) {
		cout << "已更新游戏状态" << endl;
	}
}

void Game::Render()
{
	// 渲染游戏画面的逻辑
	if (CurrentState == GameState::Menu)
	{
		cout
		<< "=====菜单=====\n"
		<< "b.开始游戏\n"
		<< "q.退出\n";
	}
	else if (CurrentState == GameState::Battle)
	{
		std::cout
			<< "=====战斗中=====\n";
	}
}

void Game::EnterBattle()
{
	battleManager->InitializeBattle();
	battleManager->ManageBattle();
	//battleManager->DisplayInfo();
	battleManager.reset();
}

void Game::ClearScreen()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}