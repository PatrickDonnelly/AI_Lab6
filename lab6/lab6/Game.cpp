/// <summary>
/// </summary>

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1250U, 1000U, 32U }, "Flow Field Pathfinding" },
	m_exitGame{false} //when true game will exit
{
	m_grid = new Grid();
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::C == t_event.key.code)
	{
		for (int i{}; i < 50; ++i)
		{
			for (int j{}; j < 50; ++j)
			{
				if (m_grid->m_tiles.at(i).at(j)->showCost)
				{
					m_grid->m_tiles.at(i).at(j)->showCost = false;
				}
				else 
				{
					m_grid->m_tiles.at(i).at(j)->showCost = true;
				}
			}
		}
	}
	if (sf::Keyboard::V == t_event.key.code)
	{
		for (int i{}; i < 50; ++i)
		{
			for (int j{}; j < 50; ++j)
			{
				if (m_grid->m_tiles.at(i).at(j)->showVectorField)
				{
					m_grid->m_tiles.at(i).at(j)->showVectorField = false;
				}
				else
				{
					m_grid->m_tiles.at(i).at(j)->showVectorField = true;
				}
			}
		}
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_grid->update(t_deltaTime, m_window);
}

void Game::render()
{
	m_window.clear(sf::Color::Red);
	m_grid->render(&m_window);
	m_window.display();
}
