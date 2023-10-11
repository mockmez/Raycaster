#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>

inline double deg_to_rad(double deg) {
	return (PI * deg) / 180;
}

sf::RectangleShape* check_player_collsion_tile(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) {

	for (int i = 0; i < tile_arr.size(); i++) {
		if (player.getGlobalBounds().intersects(tile_arr[i].getGlobalBounds())) {
			std::cout << "Collision occured \n";
			return &tile_arr[i];
		}
	}

	return nullptr;

}

int check_player_collision_x(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) {

	sf::RectangleShape* collision_tile;
	
	if ((collision_tile = check_player_collsion_tile(player, tile_arr)) == nullptr)
		return 1;

	if (((player.getPosition().x - player.getRadius()) >= collision_tile->getGlobalBounds().left) && ((player.getPosition().x + player.getRadius()) <= collision_tile->getGlobalBounds().left + TILE_WIDTH)) {
		std::cout << "Collision with tile along X-axis: " << collision_tile->getGlobalBounds().left << ", " << collision_tile->getGlobalBounds().top << std::endl;
		return 0;
	}

	return 1;

}

int check_player_collision_y(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) {

	sf::RectangleShape* collision_tile;

	if ((collision_tile = check_player_collsion_tile(player, tile_arr)) == nullptr)
		return 1;

	if (((player.getPosition().y - player.getRadius()) >= collision_tile->getGlobalBounds().left) && ((player.getPosition().x + player.getRadius()) <= collision_tile->getGlobalBounds().top + TILE_HEIGHT)) {
		std::cout << "Collision with tile along Y-axis: " << collision_tile->getPosition().x << ", " << collision_tile->getPosition().y << std::endl;
		return 0;
	}

	return 1;

}

int main() {

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Raycaster");
	sf::Event event;

	for (int i = 0; i < TILE_COUNT_Y; i++) {
		for (int j = 0; j < TILE_COUNT_X; j++) {
			if (map_array[i][j] == '#') {
				tile_vector.push_back(sf::RectangleShape(sf::Vector2f(TILE_WIDTH - TILE_THICKNESS, TILE_HEIGHT - TILE_THICKNESS)));
				tile_vector[tile_vector.size() - 1].setOutlineThickness(TILE_THICKNESS);
				tile_vector[tile_vector.size() - 1].setPosition(sf::Vector2f(j * TILE_WIDTH, i * TILE_HEIGHT));
				tile_vector[tile_vector.size() - 1].setFillColor(sf::Color::Blue);
				tile_vector[tile_vector.size() - 1].setOutlineColor(sf::Color::Green);
			}
		}
	}

	player.setOutlineThickness(PLAYER_THICKNESS);
	player.setFillColor(sf::Color::Red);
	player.setOutlineColor(sf::Color::Black);
	player.setOrigin(sf::Vector2f(player.getRadius(), player.getRadius()));
	player.setPosition(sf::Vector2f(MAP_WIDTH / 2, MAP_HEIGHT / 2));

	player_dir.setPosition(player.getPosition());
	player_dir.setFillColor(sf::Color::Black);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else {
					if (event.key.code == sf::Keyboard::Z) {
						
						player.setPosition(sf::Vector2f(player.getPosition().x + step_x * check_player_collision_x(player, tile_vector), player.getPosition().y + step_y * check_player_collision_y(player, tile_vector)));
					}
					if (event.key.code == sf::Keyboard::S) {
						
						player.setPosition(sf::Vector2f(player.getPosition().x - step_x * check_player_collision_x(player, tile_vector), player.getPosition().y - step_y * check_player_collision_y(player, tile_vector)));
					}

					if (event.key.code == sf::Keyboard::Q) {

						player.setRotation(player.getRotation() - 5);

					}
					else if (event.key.code == sf::Keyboard::D) {

						player.setRotation(player.getRotation() + 5);

					}

					step_x = 5 * cos(deg_to_rad(player.getRotation()));
					step_y = 5 * sin(deg_to_rad(player.getRotation()));

				}

			}
			else if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		player_dir.setPosition(player.getPosition());
		player_dir.setRotation(player.getRotation());

		window.clear(sf::Color(200, 200, 200));

		for (int i = 0; i < tile_vector.size(); i++) {
			window.draw(tile_vector[i]);
		}

		window.draw(player);
		window.draw(player_dir);

		window.display();
		
	}

	return 0;

}
