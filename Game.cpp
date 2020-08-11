#include "Game.h"

Game::Game(int window_size) {
	this->window_size = window_size;
	cell_size = window_size / ARRAY_SIZE;
	cell_size = window_size / ARRAY_SIZE;
	
	//font.loadFromFile("calibri.ttf");

	Init();
}

void Game::Init() {
	for (size_t x = 0; x < ARRAY_SIZE; x++)
	{
		for (size_t y = 0; y < ARRAY_SIZE; y++)
		{
			cells[y][x] = false;
			next_cells[y][x] = false;

			colored_cells[y][x] = 0;
		}
	}
}

void Game::CheckClick(int screen_x, int screen_y, bool __delete__) {
	if (screen_x < 0 || screen_y < 0 || screen_x > window_size || screen_y > window_size) {
		throw CLICKED_OUT_OF_BOUNDS;
	}

	int x = screen_x / cell_size;
	int y = screen_y / cell_size;

	if(!__delete__)
	{
	cells[x][y] = true;
	next_cells[x][y] = true;

	colored_cells[y][x] = 1;
	}
	else 
	{
		cells[x][y] = false;
		next_cells[x][y] = false;

		colored_cells[y][x] = 0;
	}
	next_gen = false;
}

void Game::Logic() {
	if (paused) return;

	alive = 0;

	if (next_gen) {
		copyGen();
	}

	for (size_t x = 0; x < ARRAY_SIZE; x++)
	{
		for (size_t y = 0; y < ARRAY_SIZE; y++)
		{

			int neighbour_counter = FindNeighbours(x,y);

			if (cells[x][y] == true && (neighbour_counter < 4  && neighbour_counter > 1)) {
				next_cells[x][y] = true;
			}
			else {
				next_cells[x][y] = false;

			}

			if (cells[x][y] == false && neighbour_counter == 3) next_cells[x][y] = true;

			if (cells[x][y] == true) {
				alive++;
				colored_cells[x][y] = neighbour_counter;
			}
		}
	}
	next_gen = true;
}

int Game::FindNeighbours(int x, int y) {
	//if (x < 0 || y < 0 || x > ARRAY_SIZE || y > ARRAY_SIZE) {
	//	throw NEIGHBOUR_CHECK_OUT_OF_BOUNDS;
	//}


	int neighbour_counter = 0;

	for (int x_check = x - 1; x_check <= x + 1; x_check++)
	{
		for (int y_check = y - 1; y_check <= y + 1; y_check++)
		{
			//if (x_check < 0) x_check++;
			//if (y_check < 0) y_check++;

			if (x_check < 0) x_check = ARRAY_SIZE;
			if (y_check < 0) y_check = ARRAY_SIZE;

			if (x_check > ARRAY_SIZE) x_check = 0;
			if (y_check > ARRAY_SIZE) y_check = 0;

			if (x_check == x && y_check == y) continue;

			//if (x_check > ARRAY_SIZE || y_check > ARRAY_SIZE) continue;

			if (cells[x_check][y_check] == true) neighbour_counter++;
		}
	}

	return neighbour_counter;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();

	sf::Color color = sf::Color(254, 254, 254);
	if (paused) color = sf::Color(254, 0, 0);

	if(paused)
	{
	// Drawing vertical lines
	for (size_t x = 0; x < window_size; x += cell_size)
	{
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(x, 0);
		lines[0].color = color;
		lines[1].position = sf::Vector2f(x, window_size);
		lines[1].color = color;
		target.draw(lines, states);
	}

	// Drawing Horizontal lines
	for (size_t y = 0; y < window_size; y += cell_size)
	{
		sf::VertexArray lines(sf::LinesStrip, 2);
		lines[0].position = sf::Vector2f(0, y);
		lines[0].color = color;
		lines[1].position = sf::Vector2f(window_size, y);
		lines[1].color = color;
		target.draw(lines, states);

	}
	}
	
	for (size_t x = 0; x < ARRAY_SIZE; x++)
	{
		for (size_t y = 0; y < ARRAY_SIZE; y++)
		{
			if (cells[x][y] == true) 
			{
				sf::Color cell_color = color;
				sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));

				if(colored_mode)
				{
				switch (colored_cells[x][y])
				{
				case 1:
					cell_color = sf::Color(254, 254, 0);
					break;

				case 2:
					cell_color = sf::Color(254, 218, 0);
					break;

				case 3:
					cell_color = sf::Color(254, 182, 0);
					break;

				case 4:
					cell_color = sf::Color(254, 146, 0);
					break;

				case 5:
					cell_color = sf::Color(254, 110, 0);
					break;

				case 6:
					cell_color = sf::Color(254, 74, 0);
					break;

				case 7:
					cell_color = sf::Color(254, 38, 0);
					break;

				case 8:
					cell_color = sf::Color(1000, 0, 0);
					break;
				}
				}
				cell.setFillColor(cell_color);
				cell.setOutlineColor(sf::Color::Transparent);
				cell.setPosition(x * cell_size, y * cell_size);
				target.draw(cell, states);

			}
		}
	}

	
	//sf::Text text("", font, 52);
	//text.setOutlineColor(color);
	//text.setFillColor(color);
	//if (paused) text.setString("Paused");
}

void Game::changePause() {
	paused = !paused;
}
void Game::changeColorMode() 
{
	colored_mode = !colored_mode;
}
void Game::copyGen() {
	for (size_t x = 0; x < ARRAY_SIZE; x++)
	{
		for (size_t y = 0; y < ARRAY_SIZE; y++)
		{
			cells[y][x] = next_cells[y][x];
		}
	}
}

Game::~Game(){
	
}