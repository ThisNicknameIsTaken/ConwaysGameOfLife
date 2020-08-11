#ifndef __GAME_OF_LIFE__

#define __GAME_OF_LIFE__

#define CLICKED_OUT_OF_BOUNDS
#define NEIGHBOUR_CHECK_OUT_OF_BOUNDS

#define ARRAY_SIZE 50

#include <SFML/Graphics.hpp>


class Game : public sf::Drawable, public sf::Transformable
{
public:
	Game(int window_size);
	~Game();

	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void changePause();
	void changeColorMode();
	void CheckClick(int screen_x, int screen_y, bool __delete__);
	void Logic();

private:
	void Init();
		
	int FindNeighbours(int x, int y);
	void copyGen();


	bool cells[ARRAY_SIZE][ARRAY_SIZE];
	bool next_cells[ARRAY_SIZE][ARRAY_SIZE];

	int colored_cells[ARRAY_SIZE][ARRAY_SIZE];


	bool next_gen = false;

	bool paused = true;
	int window_size;
	int cell_size;
	int alive = 0;

	bool colored_mode = true;

	//sf::Font font;
};




#endif // !__GAME_OF_LIFE__

