#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "CastomTexture.h"
#include "CastomText.h"
#include "settings.h"
#include "Location.h"
#include "btns.h"
class Player {
public:
	float x = 1.5, y = 1.5;
	float angle = 0;
	char numLvl = 0;
	Player(int) {
		std::fstream file;
		file.open("resources\\saves\\info.txt");
		file.read((char*)&numLvl, 1);
		file.close();

		if (numLvl != 0) {
			x = worldMap[numLvl].startX + 0.5;
			y = worldMap[numLvl].startY + 0.5;
		}
	}
	void save() {
		std::fstream file;
		file.open("resources\\saves\\info.txt");
		file.write((char*)&numLvl, 1);
		file.close();
	}
};
Player player(NULL);

void PlayerControl(sf::RenderWindow* window) {
	static bool BtnR = 0;

	char sumbvol = worldMap[player.numLvl].loc[(int)player.y][(int)player.x];

	if (sumbvol == '/') {
		text.text.setString("press \"R\"");
		text.text.setPosition(50, 400);
		window->draw(text.text);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && BtnR == 0) {
			BtnR = 1;
			player.numLvl++;
			player.x = worldMap[player.numLvl].startX + 0.5;
			player.y = worldMap[player.numLvl].startY + 0.5;
		}
	}
	else if (sumbvol == '.') {
		text.text.setString("press \"R\"");
		text.text.setPosition(50, 400);
		window->draw(text.text);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && BtnR == 0) {
			BtnR = 1;
			player.numLvl--;
			player.x = worldMap[player.numLvl].endX + 0.5;
			player.y = worldMap[player.numLvl].endY + 0.5;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		BtnR = 0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		float newx = player.x + cosf(player.angle - pi / 2) * 0.05;
		if (worldMap[player.numLvl].loc[(int)player.y][(int)newx] < '0')
			player.x = newx;

		float newy = player.y + sinf(player.angle - pi / 2) * 0.05;
		if (worldMap[player.numLvl].loc[(int)newy][(int)player.x] < '0')
			player.y = newy; 
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		float newx = player.x + cosf(player.angle + pi / 2) * 0.05;
		if (worldMap[player.numLvl].loc[(int)player.y][(int)newx] < '0')
			player.x = newx;

		float newy = player.y + sinf(player.angle + pi / 2) * 0.05;
		if (worldMap[player.numLvl].loc[(int)newy][(int)player.x] < '0')
			player.y = newy;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		float newx = player.x + cosf(player.angle) * 0.05;
		if (worldMap[player.numLvl].loc[(int)player.y][(int)newx] < '0')
			player.x = newx;

		float newy = player.y + sinf(player.angle) * 0.05;
		if (worldMap[player.numLvl].loc[(int)newy][(int)player.x] < '0')
			player.y = newy;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		float newx = player.x - cosf(player.angle) * 0.05;
		if (worldMap[player.numLvl].loc[(int)player.y][(int)newx] < '0')
			player.x = newx;

		float newy = player.y - sinf(player.angle) * 0.05;
		if (worldMap[player.numLvl].loc[(int)newy][(int)player.x] < '0')
			player.y = newy;
	}

	if (player.angle < -pi)
		player.angle = pi;
	else if (player.angle > pi)
		player.angle = -pi;
}

void rayCadting(sf::RenderWindow* window) {
	for (int i = 0; i < numRays; i++) {

		float rayAngle = player.angle - halfFov + (i * fov / numRays);

		sf::Vector2f rayPos(player.x, player.y);
		sf::Vector2f move(cosf(rayAngle) * 0.05, sinf(rayAngle) * 0.05);

		for (float j = 1; j < 100; j++) {
			rayPos.x += move.x;
			rayPos.y += move.y;
			char sumbvol = worldMap[player.numLvl].loc[(int)rayPos.y][(int)rayPos.x];
			if (sumbvol > '/' && sumbvol <= '9') {
				float floatX = rayPos.x - (int)rayPos.x;
				float floatY = rayPos.y - (int)rayPos.y; // то, насколько луч вошёл внутрь блока

				if (floatX - move.x > 0 && (floatY - move.y < 0 || floatY - move.y > 1)) {
					line.sprite.setTextureRect(sf::IntRect(
						(sumbvol - '0') * 31 + floatX * 31, 0, 1, 31)
					);
				}
				else {
					line.sprite.setTextureRect(sf::IntRect(
						(sumbvol - '0') * 31 + floatY * 31, 0, 1, 31)
					);
				}

				line.sprite.setSize(sf::Vector2f(
					screenSizeX / numRays,
					dist / (j * cosf(player.angle - rayAngle))
				));
				line.sprite.setPosition(i * (screenSizeX / numRays), screenSizeY / 2 - line.sprite.getSize().y / 2);

				char col = 255 - 255 * j / 100;
				line.sprite.setFillColor(sf::Color(col, col, col));

				window->draw(line.sprite);

				break;
			}
		}
	}
}