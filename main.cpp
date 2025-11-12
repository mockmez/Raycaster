#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

const double PI = 3.141592653589793238462643383279502884197;

const int SCREEN_WIDTH = 1200, SCREEN_HEIGHT = 600;
const int MAP_HEIGHT = 600, MAP_WIDTH = 600;

const int TILE_COUNT_X = 10, TILE_COUNT_Y = 10;
const int TILE_WIDTH = MAP_WIDTH / TILE_COUNT_X, TILE_HEIGHT = MAP_HEIGHT / TILE_COUNT_Y;
const int TILE_THICKNESS = 5;

const char map_array[][TILE_COUNT_X + 1] = {

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

const int PLAYER_RADIUS = 15;
const int PLAYER_THICKNESS = 5;

const int RAY_COUNT = 120;
const float AOV = 60.0f;

extern std::vector<sf::RectangleShape> rect_arr;
extern std::vector<sf::RectangleShape> ray_x_array, ray_y_array;

extern sf::CircleShape player;
extern sf::RectangleShape player_dir;
extern float step_x, step_y;
extern std::vector<sf::RectangleShape> tile_vector;

sf::CircleShape player(PLAYER_RADIUS);
sf::RectangleShape player_dir(sf::Vector2f(PLAYER_RADIUS, 2));
float step_x = 0.f, step_y = 0.f;

std::vector<sf::RectangleShape> tile_vector, rect_arr, ray_x_array, ray_y_array;

sf::RectangleShape* check_player_collsion_tile(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) 
{
	for (int i = 0; i < tile_arr.size(); i++) {
		if (player.getGlobalBounds().intersects(tile_arr[i].getGlobalBounds())) {
			std::cout << "Collision occured \n";
			return &tile_arr[i];
		}
	}
	return nullptr;
}

int check_player_collision_x(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) 
{
	sf::RectangleShape* collision_tile;

	if ((collision_tile = check_player_collsion_tile(player, tile_arr)) == nullptr)
		return 1;
	if (((player.getPosition().x - player.getRadius()) >= collision_tile->getGlobalBounds().left) && ((player.getPosition().x + player.getRadius()) <= collision_tile->getGlobalBounds().left + TILE_WIDTH)) {
		std::cout << "Collision with tile along X-axis: " << collision_tile->getGlobalBounds().left << ", " << collision_tile->getGlobalBounds().top << std::endl;
		return 0;
	}
	return 1;
}

int check_player_collision_y(sf::CircleShape& player, std::vector <sf::RectangleShape>& tile_arr) 
{
	sf::RectangleShape* collision_tile;

	if ((collision_tile = check_player_collsion_tile(player, tile_arr)) == nullptr)
		return 1;
	if (((player.getPosition().y - player.getRadius()) >= collision_tile->getGlobalBounds().left) && ((player.getPosition().x + player.getRadius()) <= collision_tile->getGlobalBounds().top + TILE_HEIGHT)) {
		std::cout << "Collision with tile along Y-axis: " << collision_tile->getPosition().x << ", " << collision_tile->getPosition().y << std::endl;
		return 0;
	}
	return 1;
}

inline double deg_to_rad(double deg)
{
	return (PI * deg) / 180;
}

int game_func() 
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "The Title");
	window.setFramerateLimit(60);
	sf::RectangleShape map(sf::Vector2f(480, 600));
	map.setFillColor(sf::Color(255, 255, 255));

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
			if (event.type == sf::Event::Closed) 
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape) 
					window.close();
				else if (event.key.code == sf::Keyboard::Q) 
					player.setRotation(player.getRotation() - 5);
				else if (event.key.code == sf::Keyboard::D) 
					player.setRotation(player.getRotation() + 5);
				else if (event.key.code == sf::Keyboard::Z) 
					player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 5));
				else if (event.key.code == sf::Keyboard::S) 
					player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - 5));
			}
		}

		for (int i = 0; i < RAY_COUNT; i++) {
			ray_x_array[i].setRotation((-1 * (AOV / 2.0f)) + i * (AOV / RAY_COUNT) + player.getRotation());
			ray_y_array[i].setRotation((-1 * (AOV / 2.0f)) + i * (AOV / RAY_COUNT) + player.getRotation());
			ray_x_array[i].setPosition(player.getPosition());
			ray_y_array[i].setPosition(player.getPosition());
		}
		
/*
		for (int i = 0; i < RAY_COUNT; i++) {
			ray_x_array[i].setSize(sf::Vector2f(inBox_xComponent, ray_x_array[i].getSize().y));
			ray_y_array[i].setSize(sf::Vector2f(inBox_yComponent, ray_y_array[i].getSize().y));
		}
*/
		window.clear(sf::Color::White);
		window.draw(map);

		for (int i = 0; i < rect_arr.size(); i++) 
			window.draw(rect_arr[i]);
		
		window.draw(player);

		for (int i = 0; i < RAY_COUNT; i++) {
			window.draw(ray_x_array[i]);
			window.draw(ray_y_array[i]);
		}

		window.display();
	}

	return 0;
}

int main() 
{
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
				if (event.key.code == sf::Keyboard::Escape) 
					window.close();
				else {
					if (event.key.code == sf::Keyboard::Z) 
						player.setPosition(sf::Vector2f(player.getPosition().x + step_x * check_player_collision_x(player, tile_vector), player.getPosition().y + step_y * check_player_collision_y(player, tile_vector)));
					if (event.key.code == sf::Keyboard::S) 
						player.setPosition(sf::Vector2f(player.getPosition().x - step_x * check_player_collision_x(player, tile_vector), player.getPosition().y - step_y * check_player_collision_y(player, tile_vector)));
					if (event.key.code == sf::Keyboard::Q) 
						player.setRotation(player.getRotation() - 5);
					else if (event.key.code == sf::Keyboard::D) 
						player.setRotation(player.getRotation() + 5);
					step_x = 5 * cos(deg_to_rad(player.getRotation()));
					step_y = 5 * sin(deg_to_rad(player.getRotation()));
				}
			}
			else if (event.type == sf::Event::Closed) 
				window.close();
		}

		player_dir.setPosition(player.getPosition());
		player_dir.setRotation(player.getRotation());

		window.clear(sf::Color(200, 200, 200));

		for (int i = 0; i < tile_vector.size(); i++)
			window.draw(tile_vector[i]);
		window.draw(player);
		window.draw(player_dir);
		window.display();
	}

	return 0;
}

