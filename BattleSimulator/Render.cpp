#include "Render.h"
#include "Character.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <vector>

void Render::WaitForDisplay(int seconds)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(seconds));
}

void Render::SetTextColor(TextColor color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

void Render::RenderText(const std::string& s, TextColor color)
{
	SetTextColor(color);
	std::cout << s;
	SetTextColor(TextColor::White);
}

std::ostream& operator<<(std::ostream& os, Character& character)
{
	CharacterInfo info = character.GetInfo();
	os << "Name: " << info.Name << ", HP: " << info.HP;
	os << "  Attack: " << info.Attack << ", Defense: " << info.Defense << "\n";
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

void Render::CoutCharacter(CharacterInfo& infoBegin, CharacterInfo& infoEnd)
{
	std::cout << "Name: " << infoBegin.Name;
	std::cout << ", HP: ";
	if (infoBegin.HP < infoEnd.HP) {
		RenderText(std::to_string(infoEnd.HP), TextColor::Green);
	}
	else if (infoBegin.HP > infoEnd.HP) {
		RenderText(std::to_string(infoEnd.HP), TextColor::Red);
	}
	else {
		std::cout << infoEnd.HP;
	}
	if (infoBegin.Attack < infoEnd.Attack) {
		std::cout << ", Attack: ";
		RenderText(std::to_string(infoEnd.Attack), TextColor::Blue);
	}
	else if (infoBegin.Attack > infoEnd.Attack) {
		std::cout << ", Attack: ";
		RenderText(std::to_string(infoEnd.Attack), TextColor::Red);
	}
	else {
		std::cout << ", Attack: " << infoEnd.Attack;
	}
	if (infoBegin.Defense < infoEnd.Defense) {
		std::cout << ", Defense: ";
		RenderText(std::to_string(infoEnd.Defense), TextColor::Yellow);
	}
	else if (infoBegin.Defense > infoEnd.Defense) {
		std::cout << ", Defense: ";
		RenderText(std::to_string(infoEnd.Defense), TextColor::Red);
	}
	else {
		std::cout << ", Defense: " << infoEnd.Defense;
	}
	std::cout << '\n' << std::endl;
}

void Render::SetCursorPosition(short x, short y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}

COORD Render::GetCursorPosition()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole, &info);
	return info.dwCursorPosition;
}

void Render::DisplayCurrentRound(int currentRound)
{
	RenderText("\u5F53\u524D\u4E3A\u7B2C ", TextColor::White);
	RenderText(std::to_string(currentRound), TextColor::LightMagenta);
	RenderText("\u56DE\u5408\n", TextColor::White);
}

void Render::DisplaySkillList(const std::string& skillData)
{
	std::cout << "\u8BF7\u9009\u62E9\u4F60\u8981\u65BD\u653E\u7684\u6280\u80FD\n";
	size_t begin = 0;
	size_t index = 1;
	while (begin < skillData.size()) {
		size_t end = skillData.find(';', begin);
		if (end == std::string::npos) {
			break;
		}
		std::string skill = skillData.substr(begin, end - begin);
		size_t separator = skill.rfind(',');
		if (separator != std::string::npos) {
			std::cout << index << "." << skill.substr(0, separator);
			RenderText("      " + skill.substr(separator + 1), TextColor::LightBlue);
			RenderText(" \u56DE\u5408\u540E\u53EF\u7528\n", TextColor::White);
			index++;
		}
		begin = end + 1;
	}
}

void Render::DisplayAllCharacterInfo(std::string& s, const std::string& previousData)
{
	size_t pos = s.find(';');
	std::string p1 = s.substr(0, pos);
	std::string p2 = s.substr(pos + 1);
	CharacterInfo pInfo1 = AnalysisPlayerData(1, p1);
	CharacterInfo pInfo2 = AnalysisPlayerData(2, p2);
	if (previousData.empty()) {
		Render::CoutCharacter(pInfo1, pInfo1);
		Render::CoutCharacter(pInfo2, pInfo2);
		return;
	}

	size_t previousPos = previousData.find(';');
	std::string previousP1 = previousData.substr(0, previousPos);
	std::string previousP2 = previousData.substr(previousPos + 1);
	CharacterInfo previousPInfo1 = AnalysisPlayerData(1, previousP1);
	CharacterInfo previousPInfo2 = AnalysisPlayerData(2, previousP2);
	Render::CoutCharacter(previousPInfo1, pInfo1);
	Render::CoutCharacter(previousPInfo2, pInfo2);
}

void Render::DisplayActionMessage(const std::string& s)
{
	const std::string useText = "\u4F7F\u7528 ";
	const std::string skillEndText = ",\n";
	size_t usePosition = s.find(useText);
	if (usePosition == std::string::npos) {
		RenderText(s, TextColor::White);
		return;
	}

	size_t skillPosition = usePosition + useText.size();
	size_t skillEndPosition = s.find(skillEndText, skillPosition);
	if (skillEndPosition == std::string::npos) {
		RenderText(s, TextColor::White);
		return;
	}

	size_t valuePosition = s.find_first_of("0123456789", skillEndPosition);
	if (valuePosition == std::string::npos) {
		RenderText(s, TextColor::White);
		return;
	}
	size_t valueEndPosition = s.find_first_not_of("0123456789", valuePosition);
	if (valueEndPosition == std::string::npos) {
		valueEndPosition = s.size();
	}

	TextColor valueColor = TextColor::White;
	if (s.find("\u70B9\u4F24\u5BB3", valueEndPosition) != std::string::npos) {
		valueColor = TextColor::LightRed;
	}
	else if (s.find("\u70B9\u8840\u91CF", valueEndPosition) != std::string::npos) {
		valueColor = TextColor::LightGreen;
	}
	else if (s.find("\u70B9\u9632\u5FA1", valueEndPosition) != std::string::npos) {
		valueColor = TextColor::LightBlue;
	}

	RenderText(s.substr(0, skillPosition), TextColor::White);
	RenderText(s.substr(skillPosition, skillEndPosition - skillPosition), TextColor::LightCyan);
	RenderText(s.substr(skillEndPosition, valuePosition - skillEndPosition), TextColor::White);
	RenderText(s.substr(valuePosition, valueEndPosition - valuePosition), valueColor);
	RenderText(s.substr(valueEndPosition), TextColor::White);
}

CharacterInfo Render::AnalysisPlayerData(int index, std::string& s)
{
	CharacterInfo p;
	p.Name = "\u73A9\u5BB6" + std::to_string(index);
	size_t pos;
	std::vector<int> values;
	while ((pos = s.find(',')) != std::string::npos) {
		values.push_back(std::stoi(s.substr(0, pos)));
		s = s.substr(pos + 1);
	}
	p.HP = values[0];
	p.Attack = values[1];
	p.Defense = values[2];
	return p;
}
