#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <array>
#include <queue>
#include <iostream>
#include <list>

class Grid
{
private:
	void setStartTile(sf::RenderWindow& t_window);
	void setGoalTile(sf::RenderWindow& t_window);

	Tile* m_startingTile{ nullptr };
	Tile* m_goalTile{ nullptr };

public:
	sf::Clock timer;
	sf::CircleShape m_npc;
	float m_speed;
	float m_velocity;
	sf::Vector2f m_direction;
	std::list<sf::Vector2i> path{};
	sf::Vector2f prevPos{};
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
	sf::Text m_helpText;
	sf::RectangleShape m_background;

	Grid();
	float m_width = 20.0f;
	void render(sf::RenderWindow* t_window);
	void update(sf::Time t_deltaTime, sf::RenderWindow& m_window);
	std::array<std::array<Tile*, 50>, 50> m_tiles{ nullptr }; // 2D Array of tile pointers 50 x 50
	void placeRemove();
	void costField();
	bool noPath = false;
};
#endif // !GRID_HPP

