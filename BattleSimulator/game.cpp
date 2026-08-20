#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "Render.h"

using namespace std;

Game::Game() : isRunning(true) {
	CurrentState = GameState::Menu;
}

void Game::Run()
{
	Render::RenderText("欢迎来到战斗模拟器！\n", TextColor::White);
	cout
		<< "=====菜单=====\n"
		<< "b.开始游戏\n"
		<< "q.退出\n"
		<< "n.联机对战";

	while (isRunning) {
		Input();
		if (Game::isRunning == false) {
			cout << "已退出" << endl;
			break;
		}else if (CurrentState==GameState::Battle) {
			Render::ClearScreen();
			cout << "进入战斗   " << "z退出" << endl;
			CurrentState = GameState::Battle;
			battleManager = std::make_unique<BattleManager>();
			//这里忘记初始化了，battlemanager没有实例化，后续指针赋值给player时找不到对象，报this为nullptr的错。
			EnterBattle();
			CurrentState = GameState::Menu;
		}
		else if (CurrentState == GameState::Network) {
			client.ManageCommunication();
			CurrentState = GameState::Menu;
		}
		Render::ClearScreen();
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
	else if (command == 'z' && CurrentState != GameState::Menu) {
		CurrentState = GameState::Menu;
	}
	else if (command == 'n' && CurrentState != GameState::Network) {
		CurrentState = GameState::Network;
	}
}

void Game::Render()
{
	// 渲染游戏画面的逻辑
	if (CurrentState == GameState::Menu)
	{
		cout
		<< "欢迎来到战斗模拟器！\n"
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

