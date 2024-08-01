#pragma once
#include <SFML/Graphics.hpp>
class CastomTexture {
public:
	sf::Texture texture;
	sf::RectangleShape sprite;
	CastomTexture(std::string name) {
		texture.loadFromFile(name);
		sprite.setTexture(&texture);
	}
};
CastomTexture line("resources\\sprites\\walls.png");