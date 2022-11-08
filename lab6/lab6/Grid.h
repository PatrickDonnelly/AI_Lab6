#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <array>

class Grid
{
private:
	void setStartTile(sf::RenderWindow& t_window);
	void setGoalTile(sf::RenderWindow& t_window);

	Tile* m_startingTile{ nullptr };
	Tile* m_goalTile{ nullptr };

public:

	Grid();
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	std::array<std::array<Tile*, 50>, 50> m_tiles{ nullptr }; // 2D Array of tile pointers 50 x 50

};
#endif // !GRID_HPP

