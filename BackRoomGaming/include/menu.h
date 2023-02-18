#pragma once
#include <functional>

struct Option
{
	int ID;
	char* Text;
	std::function<void(void)> effect;
	int width;
	int height;
	int x;
	int y;
};

struct Menu
{
	Option options[999];
};
