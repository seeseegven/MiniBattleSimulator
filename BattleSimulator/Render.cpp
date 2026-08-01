#include "Render.h"
#include <Windows.h>
#include <thread>
#include <chrono>
#include <iostream>

void Render::WaitForDisplay(int seconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(seconds));
}

void Render::SetTextColor(TextColor color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

void Render::RenderText(const std::string& s, TextColor color) {
	SetTextColor(color);
	std::cout << s;
	SetTextColor(TextColor::White);
}

std::ostream& operator<<(std::ostream& os, Character& character) {
	CharacterInfo Info = character.GetInfo();
	os << "Name: " << Info.Name << ", HP: ";
	int deltaHP = character.ChangeHP(Info.lastHP, Info.HP);
	if (deltaHP > 0) {
		Render::RenderText(std::to_string(Info.HP), TextColor::Green);
	}
	else if (deltaHP < 0) {
		Render::RenderText(std::to_string(Info.HP), TextColor::Red);
	}
	else {
		os << Info.HP;
	}
	os << "  Attack: " << Info.Attack << ", Defense: " << Info.Defense << "\n";
	return os;
}

void Render::ClearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
