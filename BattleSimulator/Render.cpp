#include "Render.h"
#include "Character.h"
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
	os << "Name: " << Info.Name << ", HP: " << Info.HP;
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

void Render::CoutCharacter(CharacterInfo& InfoBegin, CharacterInfo& InfoEnd) {
	std::cout << "Name: " << InfoBegin.Name;
	std::cout << ", HP: ";
	if (InfoBegin.HP < InfoEnd.HP) {
		RenderText(std::to_string(InfoEnd.HP), TextColor::Green);
	}else if (InfoBegin.HP > InfoEnd.HP) {
		RenderText(std::to_string(InfoEnd.HP), TextColor::Red);
	}else {
		std::cout << InfoEnd.HP;
	}
	if (InfoBegin.Attack < InfoEnd.Attack) {
		std::cout << ", Attack: ";
		RenderText(std::to_string(InfoEnd.Attack), TextColor::Blue);
	}else if (InfoBegin.Attack > InfoEnd.Attack) {
		std::cout << ", Attack: ";
		RenderText(std::to_string(InfoEnd.Attack), TextColor::Red);
	}else {
		std::cout << ", Attack: " << InfoEnd.Attack;
	}
	if (InfoBegin.Defense < InfoEnd.Defense) {
		std::cout << ", Defense: ";
		RenderText(std::to_string(InfoEnd.Defense), TextColor::Yellow);
	}else if (InfoBegin.Defense > InfoEnd.Defense) {
		std::cout << ", Defense: ";
		RenderText(std::to_string(InfoEnd.Defense), TextColor::Red);
	}else {
		std::cout << ", Defense: " << InfoEnd.Defense;
	}
	std::cout << '\n' << std::endl;
}

void Render::SetCursorPosition(short x, short y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(hConsole, pos);
}

COORD Render::GetCursorPosition() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);

	return info.dwCursorPosition;
}

void Render::DisplayAllCharacterInfo(std::string& s)
{
	size_t pos = s.find('\n');
	s = s.substr(0, pos-1);
	pos = s.find(';');
	std::string p1 = s.substr(0, pos);
	std::string p2 = s.substr(pos + 1);
	CharacterInfo pInfo1 = AnalysisPlayerData(1, p1);
	CharacterInfo pInfo2 = AnalysisPlayerData(2, p2);
	Render::CoutCharacter(pInfo1, pInfo1);
	Render::CoutCharacter(pInfo2, pInfo2);
}

CharacterInfo Render::AnalysisPlayerData(int index, std::string& s)
{

	CharacterInfo p;
	p.Name = "Íæ¼Ò" + std::to_string(index);
	size_t pos;
	std::vector<int> values;
	while ((pos = s.find(',')) != std::string::npos) {
		values.push_back(std::stoi(s.substr(0, pos)));
		s = s.substr(pos+1);
		//100,30,;
	}
	p.HP = values[0];
	p.Attack = values[1];
	p.Defense = values[2];
	return p;
}
