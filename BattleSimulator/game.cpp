#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : isRunning(true) {
	currentState = GameState::Menu;
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
		}
		Update();
		Render();
	}
}

void Game::Input()
{
	//处理输入的逻辑
	char command;
	cout << "请输入指令，q退出";
	cin >> command;

	if (command == 'q') {
		isRunning = false;
	}
	else if (command == 'b') {
		currentState = GameState::Battle;
		cout << "进入战斗" << endl;
	}
}

void Game::Update()
{
	// 更新游戏状态的逻辑
	if (currentState == GameState::Battle) {
		cout << "战斗逻辑更新" << endl;
	}
}

void Game::Render()
{
	// 渲染游戏画面的逻辑
	if (currentState == GameState::Menu)
	{
		cout
		<< "=====菜单=====\n"
		<< "b.开始游戏\n"
		<< "q.退出\n";
	}
	else if (currentState == GameState::Battle)
	{
		std::cout
			<< "=====战斗中=====\n";
	}
}