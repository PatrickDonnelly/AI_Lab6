#include "Grid.h"

Grid::Grid()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			m_tiles.at(i).at(j) = new Tile();
			m_tiles.at(i).at(j)->setPosition(m_tiles.at(i).at(j)->m_width * i, m_tiles.at(i).at(j)->m_width * j);
		}
	}
	m_startingTile = m_tiles.at(5).at(5);
	m_tiles.at(5).at(5)->setColour(sf::Color::Blue);
	m_goalTile = m_tiles.at(30).at(30);
	m_tiles.at(30).at(30)->setColour(sf::Color::Red);
}

void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		setStartTile(m_window);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		setGoalTile(m_window);
	}
}

void Grid::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			m_tiles.at(i).at(j)->render(t_window);
		}
	}
}

void Grid::setStartTile(sf::RenderWindow& t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (m_tiles.at(i).at(j)->getTile().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (m_tiles.at(i).at(j) != m_goalTile)
				{
					m_startingTile->setColour(sf::Color::Black);
					m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
					m_startingTile = m_tiles.at(i).at(j);
				}
			}
		}
	}
}



void Grid::setGoalTile(sf::RenderWindow& t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (m_tiles.at(i).at(j)->getTile().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
			{
				if (m_tiles.at(i).at(j) != m_startingTile)
				{
					m_goalTile->setColour(sf::Color::Black);
					m_tiles.at(i).at(j)->setColour(sf::Color::Red);
					m_goalTile = m_tiles.at(i).at(j);
				}
			}
		}
	}
}

