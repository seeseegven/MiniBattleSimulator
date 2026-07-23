#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : isRunning(true) {}

void Game::Run()
{
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
}

void Game::Update()
{
	// 更新游戏状态的逻辑
	cout << "已更新逻辑" << endl;
}

void Game::Render()
{
	// 渲染游戏画面的逻辑
	cout << "已渲染画面" << endl;
}