#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"

class Btn {
public:
	const char* str;
	unsigned short x = 0, y = 0;
	bool isTouch : 1;
	bool isPress : 1;
	Btn(sf::Vector2f pos, const char* string) {
		str = string;
		x = pos.x;
		y = pos.y;
	}
};
Btn btns[] = {
	Btn(sf::Vector2f(100, 150), "Continue"),
	Btn(sf::Vector2f(100, 210), "Save game"),
	Btn(sf::Vector2f(100, 270), "Out game")
};

bool mouseBtnLeft = 0;