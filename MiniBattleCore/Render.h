#pragma once
#include <string>
#include <cstdlib>
#include <functional>
#include <Windows.h>

class Character;
struct CharacterInfo;

enum class TextColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Render {
public:
	static void RenderText(const std::string& s, TextColor color = TextColor::Red);
	static void WaitForDisplay(int seconds = 1000);
	static void ClearScreen();
	static void CoutCharacter(CharacterInfo& infoBegin, CharacterInfo& infoEnd);
	static void SetCursorPosition(short x, short y);
	static COORD GetCursorPosition();
	static void DisplayAllCharacterInfo(std::string& s);
private:
	static void SetTextColor(TextColor color);
	static CharacterInfo AnalysisPlayerData(int index, std::string& s);
};
