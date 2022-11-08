#include "Grid.h"

Grid::Grid()
{
	setUpFont();
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			m_tiles.at(i).at(j) = new Tile(m_textFont);
			m_tiles.at(i).at(j)->setPosition(m_tiles.at(i).at(j)->m_width * i, m_tiles.at(i).at(j)->m_width * j);
			m_tiles.at(i).at(j)->rowColumn = sf::Vector2i{ i,j };
		}
	}
	m_startingTile = m_tiles.at(5).at(5);
	m_tiles.at(5).at(5)->setColour(sf::Color::Blue);
	m_goalTile = m_tiles.at(30).at(30);
	m_tiles.at(30).at(30)->setColour(sf::Color::Red);
	m_tileQueue.push(m_startingTile);
}

void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{

	}
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
	while (!m_tileQueue.empty())
	{
		costField();
		m_tileQueue.pop();
	}
}

void Grid::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			//cost =
			m_tiles.at(i).at(j)->m_text.setPosition(m_tiles.at(i).at(j)->m_width*i, m_tiles.at(i).at(j)->m_width*j);
			m_tiles.at(i).at(j)->m_text.setString(std::to_string(m_tiles.at(i).at(j)->m_cost));
			m_tiles.at(i).at(j)->render(t_window);

		}
	}
}

void Grid::costField()
{
	for (int direction = 0; direction < 9; direction++)
	{
		m_startingTile->m_cost = 0;
		if (direction == 4)
		{
			continue; // stops starting point being assigned a cost
		}
		
		int l_row = m_tileQueue.front()->rowColumn.x + ((direction / 3) - 1);
		int l_col = m_tileQueue.front()->rowColumn.y + ((direction % 3) - 1);

		if (l_row >= 0 && l_row < 50 && l_col >= 0 && l_col < 50)
		{
			if (m_tiles.at(l_row).at(l_col)->m_cost !=0)
			{
				continue; // stops endless loop
			}
			int cost = m_tiles.at(m_tileQueue.front()->rowColumn.x).at(m_tileQueue.front()->rowColumn.y)->m_cost + 1;
			m_tiles.at(l_row).at(l_col)->m_cost = cost;
			m_tileQueue.push(m_tiles.at(l_row).at(l_col));
		}
	}
}

void Grid::setStartTile(sf::RenderWindow& t_window)
{
	//m_list.empty();
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
					m_tileQueue.push(m_startingTile);
				}
			}
			m_tiles.at(i).at(j)->m_cost = 0;
			m_tiles.at(i).at(j)->m_text.setString(" ");
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

