#pragma once
#include <SFML/Graphics.hpp>
sf::Font font;
class CastomText {
public:
	sf::Text text;
	CastomText(int) {
		text.setFont(font);
		text.setCharacterSize(50);
	}
	CastomText(int size, sf::Color color, sf::Vector2f pos, std::string str) {
		text.setFont(font);
		text.setFillColor(color);
		text.setCharacterSize(size);
		text.setPosition(pos);
		text.setString(str);
	}
};
CastomText text(NULL);