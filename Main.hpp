const double PI = 3.141592653589793238462643383279502884197;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const int MAP_HEIGHT = 600;
const int MAP_WIDTH = 600;

const int TILE_COUNT_X = 10;
const int TILE_COUNT_Y = 10;
const int TILE_WIDTH = MAP_WIDTH / TILE_COUNT_X;
const int TILE_HEIGHT = MAP_HEIGHT / TILE_COUNT_Y;
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

std::vector <sf::RectangleShape> tile_vector;
sf::CircleShape player(PLAYER_RADIUS);
sf::RectangleShape player_dir(sf::Vector2f(PLAYER_RADIUS, 2));

double step_x;
double step_y;
