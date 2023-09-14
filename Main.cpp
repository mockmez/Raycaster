#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

//CONSTANTS

const double PI = 3.14159265358979323846;

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

/*Raycaster Constants*/
const int CAMERA_PLANE = 180;
const int FOV = 60;
const int HALF_FOV = FOV / 2;
const int RAY_COUNT = 20;
const float DEPTH_OF_VIEW = sqrt((SCREEN_WIDTH * SCREEN_WIDTH) + (SCREEN_HEIGHT * SCREEN_HEIGHT));

//VARIABLES

/*Player variables*/

double step_x_comp;
double step_y_comp;

long circle_x_pos;
long circle_y_pos;

double prev_angle;
double current_angle;

long curr_x;
long curr_y;

int player_quad;

/*Tile variables*/

long rect_width;
long rect_height;

double rect_x_pos;
double rect_y_pos;

double tile_x_pos;
double tile_y_pos;

/*Map vectors*/

std::vector<sf::RectangleShape> tile_arr;
std::vector<sf::RectangleShape> ray_arr_x;
std::vector<sf::RectangleShape> ray_arr_y;

//FUNCTIONS

double deg_to_radians(double degrees) {
	return PI * degrees / 180;
}

int check_collision(std::vector<sf::RectangleShape>& obj_arr, sf::Shape& obj_1) {

	for (int i = 0; i < obj_arr.size(); i++) {

		if (obj_arr[i].getGlobalBounds().intersects(obj_1.getGlobalBounds()))
			return 1;
	}

	return 0;

}

int circle_collision_detect(sf::CircleShape& obj_circle, sf::RectangleShape& obj_rect) {

	circle_x_pos = obj_circle.getGlobalBounds().left;
	circle_y_pos = obj_circle.getGlobalBounds().top;

	rect_width = obj_rect.getGlobalBounds().width;
	rect_height = obj_rect.getGlobalBounds().height;
	rect_x_pos = obj_rect.getGlobalBounds().left;
	rect_y_pos = obj_rect.getGlobalBounds().top;
	
	if (((circle_x_pos >= rect_x_pos) && (circle_x_pos <= rect_x_pos + rect_width)) && ((circle_y_pos >= rect_y_pos) && (circle_y_pos <= rect_y_pos + rect_height))) {
		return 1;
	}
	else {
		return 0;
	}

}

int main() {

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Raycaster");
	window.setFramerateLimit(60);
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
	player.setOrigin(sf::Vector2f(player.getOrigin().x + player.getRadius(), player.getOrigin().y + player.getRadius()));
	player.setPosition(sf::Vector2f((float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2));

	sf::RectangleShape pointer(sf::Vector2f(player.getRadius(), 2));
	pointer.setPosition(player.getPosition());
	pointer.setFillColor(sf::Color::Black);

	for (int i = 0; i < RAY_COUNT; i++) {
		ray_arr_x.push_back(sf::RectangleShape(sf::Vector2f(100, 2)));
		ray_arr_x[i].setPosition(player.getPosition());
		ray_arr_x[i].setFillColor(sf::Color::Yellow);
		ray_arr_x[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);

		ray_arr_y.push_back(sf::RectangleShape(sf::Vector2f(100, 2)));
		ray_arr_y[i].setPosition(player.getPosition());
		ray_arr_y[i].setFillColor(sf::Color::Green);
		ray_arr_y[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);

	}

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
					player.setRotation(player.getRotation() - 5);
					pointer.setRotation(player.getRotation());
					current_angle = pointer.getRotation();
					for (int i = 0; i < RAY_COUNT; i++) {
						ray_arr_x[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);
						ray_arr_y[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);
					}

				}
				else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					player.setRotation(player.getRotation() + 5);
					pointer.setRotation(player.getRotation());
					current_angle = pointer.getRotation();
					for (int i = 0; i < RAY_COUNT; i++) {
						ray_arr_x[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);
						ray_arr_y[i].setRotation((player.getRotation() - HALF_FOV) + i * (float)FOV / RAY_COUNT);
					}
				}
				else {

					if (current_angle != prev_angle) {
						step_x_comp = 5 * cos(deg_to_radians(player.getRotation()));
						step_y_comp = 5 * sin(deg_to_radians(player.getRotation()));

						prev_angle = current_angle;

					}

					for (int i = 0; i < tile_arr.size(); i++) {
						if (circle_collision_detect(player, tile_arr[i])) {
							if ((circle_x_pos >= rect_x_pos) && (circle_x_pos <= rect_x_pos + rect_width)) {
								step_x_comp = 0;
							}
							else if ((circle_y_pos >= rect_y_pos) && (circle_y_pos <= rect_y_pos + rect_height)) {
								step_y_comp = 0;
							}
						}
					}

					if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {

						player.setPosition(sf::Vector2f(player.getPosition().x + step_x_comp,
														player.getPosition().y + step_y_comp));
						pointer.setPosition(player.getPosition());

						for (int i = 0; i < RAY_COUNT; i++) {
							ray_arr_x[i].setPosition(player.getPosition());
							ray_arr_y[i].setPosition(player.getPosition());
						}

					}
					else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

						player.setPosition(sf::Vector2f(player.getPosition().x - step_x_comp,
														player.getPosition().y - step_y_comp));
						pointer.setPosition(player.getPosition());

						for (int i = 0; i < RAY_COUNT; i++) {
							ray_arr_x[i].setPosition(player.getPosition());
							ray_arr_y[i].setPosition(player.getPosition());
						}
					}

				}

			}

		}

		//RAYCASTER

		tile_x_pos = 0;
		tile_y_pos = 0;

		player_quad = player.getRotation() / 90;

		while (player.getPosition().x > tile_x_pos) {
			tile_x_pos += TILE_WIDTH;
		}

		while (player.getPosition().y > tile_y_pos) {
			tile_y_pos += TILE_HEIGHT;
		}

		if (player_quad == 1) {
			tile_x_pos -= TILE_WIDTH;

		}
		else if (player_quad == 2) {
			tile_x_pos -= TILE_WIDTH;
			tile_y_pos -= TILE_HEIGHT;
		}
		else if (player_quad == 3) {
			tile_y_pos -= TILE_HEIGHT;
		}

		for (int i = 0; i < RAY_COUNT; i++) {


			
		}

		window.clear(sf::Color::Black);

		for (int i = 0; i < tile_arr.size(); i++) {
			window.draw(tile_arr[i]);
		}

		window.draw(player);
		window.draw(pointer);

		for (int i = 0; i < ray_arr_x.size(); i++) {
			window.draw(ray_arr_x[i]);
			window.draw(ray_arr_y[i]);
		}

		window.display();

	}

	return 0;

}