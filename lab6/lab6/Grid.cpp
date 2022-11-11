#include "Grid.h"

Grid::Grid()
{
	setUpFont();
	m_npc.setRadius(m_width/2);
	m_npc.setOutlineThickness(8.0f);
	m_npc.setOutlineColor(sf::Color(sf::Color(0, 0, 0, 150)));
	//m_npc.setOrigin(12.5f,12.5f);
	m_npc.setFillColor(sf::Color(sf::Color(255, 80, 200)));

	m_background.setSize(sf::Vector2f{ 250.0f,1250.0f });
	m_background.setPosition(1000,0);
	m_background.setFillColor(sf::Color::Black);

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
	m_tiles.at(5).at(5)->setColour(sf::Color(sf::Color(0,225,0)));
	m_goalTile = m_tiles.at(49).at(49);
	m_tiles.at(49).at(49)->setColour(sf::Color::Red);
	m_goalTile->m_checked = true;
	//m_npc.setPosition(m_tiles.at(5).at(5)->getPos() + sf::Vector2f{12.5f,12.5f});
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
	m_helpText.setFont(m_textFont);
	m_helpText.setString("Right Click Mouse to \nmove Goal Position. \n\n\n\nLeft Click Mouse to \nmove Starting Position. \n\n\n\nHold Space and Left Click\nto place walls.\n\n\n\nHold Space and Right Click\nto remove walls.\n\n\n\nPress C to view \nCost Field.\n\n\n\nPress V to view\nVector Field.");
	m_helpText.setPosition(1010,200);
	m_helpText.setCharacterSize(15U);
	m_helpText.setFillColor(sf::Color::White);

}

void Grid::createPath()
{
	Tile* pathTile = m_tiles.at(m_startingTile->pathPos.x).at(m_startingTile->pathPos.y);
	m_npc.setPosition(m_startingTile->pathPos.x * m_width, m_startingTile->pathPos.y * m_width);

	path.clear();
	path.push_back(m_startingTile->pathPos);
	sf::Clock m_timer;

	while (pathTile->rowColumn != m_goalTile->rowColumn)
	{
		pathTile->setColour(sf::Color(sf::Color(225, 200, 0)));
		pathTile = m_tiles.at(pathTile->pathPos.x).at(pathTile->pathPos.y);
		path.push_back(pathTile->pathPos);
		if (m_timer.getElapsedTime().asSeconds() > 2.0f)
		{
			break;
		}
	}
}

void Grid::placeRemove()
{

}


void Grid::update(sf::Time t_deltaTime, sf::RenderWindow& m_window)
{
	//std::cout << m_npc.getPosition().x << std::endl;
	for (int i{}; i < 50; ++i)
	{
		for (int j{}; j < 50; ++j)
		{
			if (m_tiles.at(i).at(j)->getTile().getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (m_tiles.at(i).at(j) != m_goalTile && m_tiles.at(i).at(j) != m_startingTile)
					{
						m_tiles.at(i).at(j)->setColour(sf::Color::Black);
						regenerateGrid(m_window);
						createPath();
					}
					break;

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (m_tiles.at(i).at(j) != m_goalTile && m_tiles.at(i).at(j) != m_startingTile)
					{
						m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
						regenerateGrid(m_window);
						createPath();
					}
					break;

				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					if (m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
					{
						newStart = true;
						setStartTile(m_window);
						regenerateGrid(m_window);
					}
					break;
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					if (m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
					{
						newGoal = true;
						setGoalTile(m_window);
						regenerateGrid(m_window);
					}
					break;
				}
			}

		}
	}
	if (!path.empty())
	{
		float secsSince = timer.getElapsedTime().asSeconds();
		sf::Vector2i nextTile = path.front();
		if (secsSince >= 0.75f)
		{
			timer.restart();
			path.pop_front();

			sf::Vector2f pos{ static_cast<float>(nextTile.x) * m_width, static_cast<float>(nextTile.y) * m_width };

			m_npc.setPosition(pos);
			prevPos = pos;
		}
		else
		{
			sf::Vector2f nextpos{ static_cast<float>(nextTile.x) * m_width, static_cast<float>(nextTile.y) * m_width };
			sf::Vector2f dir = nextpos - prevPos;
			m_npc.setPosition(prevPos + (dir * secsSince / 0.75f));
		}
	}
}

void Grid::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_background);
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
			m_tiles.at(i).at(j)->m_text.setString(std::to_string(static_cast<int>(m_tiles.at(i).at(j)->m_integrationCost)));

				m_tiles.at(i).at(j)->drawLines(t_window);
			
		}
	}
	t_window->draw(m_helpText);
	t_window->draw(m_npc);
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
			if (m_tiles.at(l_row).at(l_col)->m_cost !=0 && m_tiles.at(l_row).at(l_col)->getTile().getFillColor() == sf::Color::Black)
			{
				continue; // stops endless loop
			}
			int cost = m_tiles.at(m_tileQueue.front()->rowColumn.x).at(m_tileQueue.front()->rowColumn.y)->m_cost + 1;
			m_tiles.at(l_row).at(l_col)->m_cost = cost;
			if (m_tiles.at(l_row).at(l_col) !=m_startingTile)
			{
				m_tiles.at(l_row).at(l_col)->setColourIntensity();
			}

			// integration cost added
			float distance = integrationField(l_row, l_col);
			m_tiles.at(l_row).at(l_col)->m_integrationCost = static_cast<float>(cost) + distance;
			m_tiles.at(l_row).at(l_col)->m_checked = true;
			m_tileQueue.push(m_tiles.at(l_row).at(l_col));

		}
	}
}

void Grid::regenerateGrid(sf::RenderWindow& t_window)
{

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
				if (m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
				{
					if (m_tiles.at(i).at(j) != m_goalTile && m_tiles.at(i).at(j) != m_startingTile)
					{
						m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
					}
					m_tiles.at(i).at(j)->m_cost = 0;
					m_tiles.at(i).at(j)->m_integrationCost = 0;
					m_tiles.at(i).at(j)->m_checked = false;
				}
				else
				{
					m_tiles.at(i).at(j)->m_checked = true;
					m_tiles.at(i).at(j)->m_vector = sf::Vector2f{};
					m_tiles.at(i).at(j)->m_cost = 9999;
					m_tiles.at(i).at(j)->m_integrationCost = 9999;
				}
		}
	}

	m_tileQueue.push(m_goalTile);

	while (!m_tileQueue.empty())
	{
		costField();
		m_tileQueue.pop();
	}

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			vectorField(i, j);
		}
	}

	if (newGoal == true)
	{
		newGoal = false;
		createPath();
	}
	if (newStart)
	{
		newStart = false;
		createPath();
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

		if (l_row >= 0 && l_row < 50 && l_col >= 0 && l_col < 50 && m_tiles.at(l_row).at(l_col)->getTile().getFillColor() != sf::Color::Black)
		{
			//std::cout << l_row << std::endl;
			if (bestPath == -1 || m_tiles.at(l_row).at(l_col)->m_integrationCost <= bestPathCost)
			{
				bestPath = direction;
				bestPathCost = m_tiles.at(l_row).at(l_col)->m_integrationCost;
				m_tiles.at(t_row).at(t_col)->pathPos = sf::Vector2i{ l_row,l_col };
				m_tiles.at(t_row).at(t_col)->m_vector = sf::Vector2f{ t_row + (bestPath / 3) - 1.0f,t_col + (bestPath % 3) - 1.0f };
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
			if (m_tiles.at(i).at(j) != m_startingTile && m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
			{
				m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
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
			if (m_tiles.at(i).at(j) != m_goalTile && m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
			{
				m_tiles.at(i).at(j)->setColour(sf::Color::Blue);
				if (m_tiles.at(i).at(j)->getTile().getGlobalBounds().contains(t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window))))
				{
					m_startingTile->setColour(sf::Color::Blue);
					m_tiles.at(i).at(j)->setColour(sf::Color(sf::Color(0, 225, 0)));
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
				if (m_tiles.at(i).at(j) != m_startingTile && m_tiles.at(i).at(j)->getTile().getFillColor() != sf::Color::Black)
				{
					m_goalTile->setColour(sf::Color::Blue);
					m_tiles.at(i).at(j)->setColour(sf::Color::Red);
					m_goalTile = m_tiles.at(i).at(j);
					m_goalTile->m_checked = true;
					m_tileQueue.push(m_goalTile);
				}
			}
		}
	}
}

