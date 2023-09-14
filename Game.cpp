/*
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

//MAP CONSTANTS
const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 960;

const int MAP_HEIGHT = SCREEN_HEIGHT;
const int MAP_WIDTH = SCREEN_WIDTH / 2;

const int TILE_COUNT_Y = 5;
const int TILE_COUNT_X = 7;

const int TILE_THICKNESS = 5;

const int TILE_HEIGHT = MAP_HEIGHT / TILE_COUNT_Y;
const int TILE_WIDTH = MAP_WIDTH / TILE_COUNT_X;

const char map_array[TILE_COUNT_Y][TILE_COUNT_X + 1] = {

	"#######",
	"#     #",
	"#     #",
	"#     #",
	"#######"

};

//PLAYER CONSTANTS

const int PLAYER_RADIUS = 10;
const int PLAYER_THICKNESS = 2;

//RAYCASTER CONSTANTS

const double PI = 22 / 7;

const int FOV = 180;
const int RAY_COUNT = 20;
const int AOV = 60;																		//AOV = Angle of View
const int HALF_AOV = AOV / 2;
const int DEPTH_OF_VIEW = sqrt((MAP_HEIGHT * MAP_HEIGHT) + (MAP_WIDTH * MAP_WIDTH));

//RAYCASTER VARIABLES

std::vector<sf::RectangleShape> rect_arr;

std::vector<sf::RectangleShape> ray_x_array;
std::vector<sf::RectangleShape> ray_y_array;



int main() {


	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Title");
	window.setFramerateLimit(60);
	sf::RectangleShape map(sf::Vector2f(480, 600));
	map.setFillColor(sf::Color(300, 300, 300));

	for (int i = 0; i < TILE_COUNT_Y; i++) {
		for (int j = 0; j < TILE_COUNT_X; j++) {
			if (map_array[i][j] == '#') {
				rect_arr.push_back(sf::RectangleShape(sf::Vector2f(TILE_WIDTH - TILE_THICKNESS, TILE_HEIGHT - TILE_THICKNESS)));
				rect_arr[rect_arr.size() - 1].setPosition((j * TILE_WIDTH) + TILE_THICKNESS, (i * TILE_HEIGHT) + TILE_THICKNESS);
				rect_arr[rect_arr.size() - 1].setFillColor(sf::Color(200, 200, 200));
				rect_arr[rect_arr.size() - 1].setOutlineThickness(TILE_THICKNESS);
				rect_arr[rect_arr.size() - 1].setOutlineColor(sf::Color::Cyan);
			}
		}
	}

	sf::CircleShape player(PLAYER_RADIUS);
	player.setFillColor(sf::Color::Red);
	player.setOrigin(sf::Vector2f(player.getPosition().x + PLAYER_RADIUS, player.getPosition().y + PLAYER_RADIUS));
	player.setOutlineColor(sf::Color::Black);
	player.setOutlineThickness(PLAYER_THICKNESS);
	player.setPosition(MAP_WIDTH / 2, MAP_HEIGHT / 2);

	for (int i = 0; i < RAY_COUNT; i++) {

		ray_x_array.push_back(sf::RectangleShape(sf::Vector2f(100, 2)));
		ray_x_array[i].setFillColor(sf::Color::Yellow);
		ray_x_array[i].setPosition(player.getPosition());

		ray_y_array.push_back(sf::RectangleShape(sf::Vector2f(10, 2)));
		ray_y_array[i].setFillColor(sf::Color::Green);
		ray_y_array[i].setPosition(player.getPosition());

	}

	while (window.isOpen()) {

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if (event.key.code == sf::Keyboard::Q) {
					player.setRotation(player.getRotation() - 5);
				}
				else if (event.key.code == sf::Keyboard::D) {
					player.setRotation(player.getRotation() + 5);
				}
				/*else if (event.key.code == sf::Keyboard::Z) {
					player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 5));
				}
				else if (event.key.code == sf::Keyboard::S) {
					player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - 5));
				}
			}

		}

		for (int i = 0; i < RAY_COUNT; i++) {

			ray_x_array[i].setRotation((-1 * HALF_AOV) + i * (AOV / RAY_COUNT) + player.getRotation());
			ray_y_array[i].setRotation((-1 * HALF_AOV) + i * (AOV / RAY_COUNT) + player.getRotation());

			ray_x_array[i].setPosition(player.getPosition());
			ray_y_array[i].setPosition(player.getPosition());

		}





		//for (int i = 0; i < RAY_COUNT; i++) {
			//ray_x_array[i].setSize(sf::Vector2f(inBox_xComponent, ray_x_array[i].getSize().y));
			//ray_y_array[i].setSize(sf::Vector2f(inBox_yComponent, ray_y_array[i].getSize().y));
		}//

		window.clear(sf::Color::White);

		window.draw(map);

		for (int i = 0; i < rect_arr.size(); i++) {
			window.draw(rect_arr[i]);
		}

		window.draw(player);

		for (int i = 0; i < RAY_COUNT; i++) {

			window.draw(ray_x_array[i]);
			window.draw(ray_y_array[i]);

		}

		window.display();

	}

	return 0;

}*/