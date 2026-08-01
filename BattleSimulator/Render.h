#pragma once
#include <string>
#include <cstdlib>
#include "Character.h"

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
	//const加了就可以传入右值，const引用可以绑定到临时对象
	//以color渲染字符串s
	static void WaitForDisplay(int seconds = 1000); //等待显示
	static void ClearScreen(); //清屏
private:
	static void SetTextColor(TextColor color); //设置文本颜色
};