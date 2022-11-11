#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <array>
#include <queue>
#include <iostream>

class Grid
{
private:
	void setStartTile(sf::RenderWindow& t_window);
	void setGoalTile(sf::RenderWindow& t_window);

	Tile* m_startingTile{ nullptr };
	Tile* m_goalTile{ nullptr };

public:
	int m_testCount = 0;
	float integrationField(int& t_row, int& t_col);
	void vectorField(int& t_row, int& t_col);
	bool newGoal = false;
	void resetGrid();
	std::queue<Tile*> m_tileQueue{};
	sf::Font m_textFont;
	void setUpFont();
	void createPath();
	void regenerateGrid(sf::RenderWindow& t_window);
	bool newStart = false;

	Grid();
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	std::array<std::array<Tile*, 50>, 50> m_tiles{ nullptr }; // 2D Array of tile pointers 50 x 50

	void costField();
	bool noPath = false;
};
#endif // !GRID_HPP

