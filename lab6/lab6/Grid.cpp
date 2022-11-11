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
			m_tiles.at(i).at(j)->m_checked = false;
			m_tiles.at(i).at(j)->m_cost = 0;
			m_tiles.at(i).at(j)->m_integrationCost = 0;

		}
	}
	m_startingTile = m_tiles.at(5).at(5);
	m_tiles.at(5).at(5)->setColour(sf::Color::Blue);
	m_goalTile = m_tiles.at(49).at(49);
	m_tiles.at(49).at(49)->setColour(sf::Color::Red);
	m_goalTile->m_checked = true;
	m_tileQueue.push(m_goalTile);
	
	while (!m_tileQueue.empty())
	{
		costField();

		m_tileQueue.pop();
	}
	for (int row = 0; row < 50; row++)
	{
		for (int col = 0; col < 50; col++)
		{
			vectorField(row, col);
		}
	}
	createPath();
}

void Grid::setUpFont()
{
	if (!m_textFont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{

	}
}

void Grid::createPath()
{
	Tile* pathTile = m_tiles.at(m_startingTile->pathPos.x).at(m_startingTile->pathPos.y);

	sf::Clock m_timer;

	while (pathTile->rowColumn != m_goalTile->rowColumn)
	{
		pathTile->setColour(sf::Color(0,255,0,125));
		pathTile = m_tiles.at(pathTile->pathPos.x).at(pathTile->pathPos.y);
	}
}

void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		newStart = true;
		setStartTile(m_window);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		newGoal = true;
		setGoalTile(m_window);
	}
	while (!m_tileQueue.empty())
	{
		costField();

		m_tileQueue.pop();
	}
	if (newGoal == true)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 50; j++)
			{
				vectorField(i, j);
			}
		}
		newGoal = false;
		createPath();
	}
	if(newStart)
	{
		setStartTile(m_window);
		newStart = false;
		createPath();
	}

}

void Grid::render(sf::RenderWindow* t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			m_tiles.at(i).at(j)->clearLines();
		}
	}
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			m_tiles.at(i).at(j)->m_text.setPosition(m_tiles.at(i).at(j)->m_width*i, m_tiles.at(i).at(j)->m_width*j);
			m_tiles.at(i).at(j)->m_text.setString(std::to_string(m_tiles.at(i).at(j)->m_integrationCost));
			m_tiles.at(i).at(j)->drawLines(t_window);
		}
	}
}

void Grid::costField()
{
	for (int direction = 0; direction < 9; direction++)
	{
		m_goalTile->m_cost = 0;
		m_goalTile->m_checked = true;
		if (direction == 4)
		{
			continue; // stops starting point being assigned a cost
		}
		
		int l_row = m_tileQueue.front()->rowColumn.x + (direction / 3) - 1;
		int l_col = m_tileQueue.front()->rowColumn.y + (direction % 3) - 1;

		if (l_row >= 0 && l_row < 50 && l_col >= 0 && l_col < 50 && m_tiles.at(l_row).at(l_col)->m_checked == false)
		{
			//m_testCount++;
			//std::cout << m_testCount << std::endl;
			if (m_tiles.at(l_row).at(l_col)->m_cost !=0)
			{
				continue; // stops endless loop
			}
			int cost = m_tiles.at(m_tileQueue.front()->rowColumn.x).at(m_tileQueue.front()->rowColumn.y)->m_cost + 1;
			m_tiles.at(l_row).at(l_col)->m_cost = cost;

			// integration cost added
			float distance = integrationField(l_row, l_col);
			m_tiles.at(l_row).at(l_col)->m_integrationCost = static_cast<float>(cost) + distance;
			m_tiles.at(l_row).at(l_col)->m_checked = true;
			m_tileQueue.push(m_tiles.at(l_row).at(l_col));

		}
	}
}

float Grid::integrationField(int& t_row, int& t_col)
{
	sf::Vector2f distance{ static_cast<float>(m_goalTile->rowColumn.x - t_row), static_cast<float>(m_goalTile->rowColumn.y - t_col) };
	float magnitude = sqrt((distance.x * distance.x) + (distance.y * distance.y));
	return magnitude;
}

void Grid::vectorField(int& t_row, int& t_col)
{

	int bestPath = -1;
	float bestPathCost = 0.0f;

	for (int direction = 0; direction < 9; direction++)
	{
		if (direction == 4)
		{
			continue;
		}

		int l_row = t_row + ((direction / 3) - 1);
		int l_col = t_col + ((direction % 3) - 1);

		if (l_row >= 0 && l_row < 50 && l_col >= 0 && l_col < 50)
		{
			//std::cout << l_row << std::endl;
			if (bestPath == -1 || m_tiles.at(l_row).at(l_col)->m_integrationCost < bestPathCost)
			{
				bestPath = direction;
				bestPathCost = m_tiles.at(l_row).at(l_col)->m_integrationCost;
				m_tiles.at(t_row).at(t_col)->pathPos = sf::Vector2i{ l_row,l_col };
				m_tiles.at(t_row).at(t_col)->m_vector = sf::Vector2f{ t_row + (bestPath / 3) - 1.0f,t_col + (bestPath % 3) - 1.0f};
			}
		}
	}
}

void Grid::resetGrid()
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (m_tiles.at(i).at(j) != m_startingTile)
			{
				m_tiles.at(i).at(j)->setColour(sf::Color::Black);
			}
			m_tiles.at(i).at(j)->clearLines();
			m_tiles.at(i).at(j)->m_vector = sf::Vector2f{};
			m_tiles.at(i).at(j)->m_checked = false;
			m_tiles.at(i).at(j)->m_cost = 0;
			m_tiles.at(i).at(j)->m_integrationCost = 0;
		}
	}
}

void Grid::setStartTile(sf::RenderWindow& t_window)
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (m_tiles.at(i).at(j) != m_goalTile)
			{
				m_tiles.at(i).at(j)->setColour(sf::Color::Black);
				if (m_tiles.at(i).at(j)->getTile().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
				{
					m_startingTile->setColour(sf::Color::Black);
					m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
					m_startingTile = m_tiles.at(i).at(j);
					//m_tileQueue.push(m_goalTile);
				}
			}
		}
	}
}



void Grid::setGoalTile(sf::RenderWindow& t_window)
{
	resetGrid();
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
					m_goalTile->m_checked = true;
					m_tileQueue.push(m_goalTile);
				}
			}
		}
	}
}

