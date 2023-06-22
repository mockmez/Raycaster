#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

//CONSTANTS

/*Map Constants*/
const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

/*Tile Constants*/
const int TILE_COUNT_X = 10;
const int TILE_COUNT_Y = 10;

const int TILE_THICKNESS = 5;

const float TILE_WIDTH = (float)SCREEN_WIDTH / TILE_COUNT_X;
const float TILE_HEIGHT = (float)SCREEN_HEIGHT / TILE_COUNT_Y;

const char MAP[TILE_COUNT_Y][TILE_COUNT_X + 1] = {

	"##########",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"#        #",
	"##########"

};

//VARIABLES

/*Map vectors*/

std::vector<sf::RectangleShape> tile_arr;

int main() {

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Raycaster");
	sf::Event event;

	for (int i = 0; i < TILE_COUNT_Y; i++) {
		for (int j = 0; j < TILE_COUNT_X; j++) {

			if (MAP[i][j] == '#') {
				tile_arr.push_back(sf::RectangleShape(sf::Vector2f(TILE_WIDTH - TILE_THICKNESS, TILE_HEIGHT - TILE_THICKNESS)));
				tile_arr[tile_arr.size() - 1].setOutlineThickness(TILE_THICKNESS);
				tile_arr[tile_arr.size() - 1].setOutlineColor(sf::Color(100, 80, 100));
				tile_arr[tile_arr.size() - 1].setPosition((j * TILE_WIDTH) + TILE_THICKNESS, (i * TILE_HEIGHT) + TILE_THICKNESS);
				tile_arr[tile_arr.size() - 1].setFillColor(sf::Color(0, 250, 0));

			}

		}
	}

	sf::CircleShape player(13);
	player.setFillColor(sf::Color::Red);
	player.setOutlineThickness(2);
	player.setOutlineColor(sf::Color::Black);
	player.setPosition(sf::Vector2f((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2));

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}

			}

		}

		window.clear(sf::Color::Black);

		for (int i = 0; i < tile_arr.size(); i++) {
			window.draw(tile_arr[i]);
		}

		window.draw(player);

		window.display();

	}

	return 0;

}