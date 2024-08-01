#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include "CastomTexture.h"
#include "CastomSound.h"
#include "CastomText.h"
#include "settings.h"
#include "Location.h"
#include "Player.h"
#include "btns.h"
using namespace sf;
RenderWindow window(VideoMode(screenSizeX, screenSizeY), "game");

int main() {
	srand(time(NULL));

	text.text.setFillColor(Color(3, 231, 243));
	font.loadFromFile("resources\\font.TTF");

	RectangleShape gameFloor;
	gameFloor.setSize(Vector2f(screenSizeX, 1));

	window.setFramerateLimit(30);
	window.setMouseCursorVisible(0);

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == event.Resized)
				window.setSize(Vector2u(window.getSize().x, window.getSize().x * 0.5));
		}

		player.angle += (Mouse::getPosition(window).x - screenSizeX / 2) * 0.001;
		// пауза
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			CastomText GameName(100, Color(3, 231, 243), Vector2f(50, 0), "Game");
			CastomSound touchBtn("resources\\sounds\\touchBtn.wav");
			CastomSound pressBtn("resources\\sounds\\pressBtn.wav");

			window.setMouseCursorVisible(1);

			bool pause = 1;

			while (window.isOpen() && pause) {
				Event event;
				while (window.pollEvent(event) || (window.isOpen() && !window.hasFocus())) {
					if (event.type == Event::Closed)
						window.close();
					else if (event.type == event.Resized)
						window.setSize(Vector2u(window.getSize().x, window.getSize().x * 0.5));
				}

				unsigned short
					GlobalX = Mouse::getPosition(window).x * screenSizeX / window.getSize().x,
					GlobalY = Mouse::getPosition(window).y * screenSizeY / window.getSize().y;

				window.clear();
				for (auto& i : btns) {

					text.text.setString(i.str);

					if (i.isPress == 1)
						text.text.setCharacterSize(45);
					else
						text.text.setCharacterSize(50);

					if (GlobalX > 100 && GlobalX < 350 && GlobalY > i.y && GlobalY < i.y + 60) {
						text.text.setPosition(i.x + 15, i.y);
						if (i.isTouch == 0)
							touchBtn.play();
						i.isTouch = 1;

						if (Mouse::isButtonPressed(Mouse::Left) && mouseBtnLeft == 0) {
							pressBtn.play();
							mouseBtnLeft = 1;
							text.text.setFillColor(Color(0, 211, 223));
							i.isPress = 1;
						}
						// кнопка отпущена
						else if (!Mouse::isButtonPressed(Mouse::Left)) {
							// если пнока меню до этого была зажата
							if (i.isPress == 1) {
								i.isPress = 0;
								if (i.str[0] == 'C') { // continue
									pause = 0;
									window.setMouseCursorVisible(0);
								}
								else if (i.str[0] == 'S') // save game
									player.save();
								else if (i.str[0] == 'O') // out game
									window.close();
							}
							mouseBtnLeft = 0;
						}
					}
					else {
						i.isTouch = 0;
						text.text.setPosition(i.x, i.y);
					}
					window.draw(text.text);
				}
				window.draw(GameName.text);
				window.display();
			}
		}

		Mouse::setPosition(Vector2i(screenSizeX / 2, screenSizeY / 2), window);

		window.clear();
		// отрисовка "пола"
		for (int i = 1; i < FloorLines; i++) {
			gameFloor.setPosition(0, screenSizeY - i);
			char col = 255 - 255 * i / FloorLines;
			gameFloor.setFillColor(Color(col, col, col));
			window.draw(gameFloor);
		}
		// рэй кастинг
		rayCadting(&window);
		// управление
		PlayerControl(&window);

		char sumbvol = worldMap[player.numLvl].loc[(int)player.y][(int)player.x];
		if (sumbvol >= '#' && sumbvol <= '-') {
			text.text.setString(worldMap[player.numLvl].dialogs[sumbvol - '#']);
			text.text.setPosition(0, 0);
			window.draw(text.text);
		}

		window.display();
	}
	return 0;
}