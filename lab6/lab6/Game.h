/// <summary>
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <array>
#include "Tile.h"
#include "Grid.h"


class Game
{
public:
	Game();
	~Game();
	void run();

private:

	Grid* m_grid{ nullptr };

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	sf::RenderWindow m_window;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

