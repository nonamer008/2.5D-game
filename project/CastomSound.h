#pragma once
#include <SFML/Audio.hpp>
sf::Sound sound;
class CastomSound {
public:
	sf::SoundBuffer buff;
	CastomSound(std::string name) {
		buff.loadFromFile(name);
	}
	void play() {
		sound.setBuffer(buff);
		sound.play();
	}
};