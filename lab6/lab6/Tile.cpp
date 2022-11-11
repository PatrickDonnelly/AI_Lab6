#include "Tile.h"

void Tile::setUpText(sf::Font& t_font)
{
	m_text.setFont(t_font);
	m_text.setString("0");
	m_text.setPosition(12.5f, 12.5f);
	m_text.setCharacterSize(10U);
	m_text.setFillColor(sf::Color::White);
}

Tile::Tile(sf::Font& t_font)
{
	setUpText(t_font);
	m_checked = false;
	m_cost = 0;
	m_integrationCost = 0.0f;
	m_tile.setSize(sf::Vector2f(m_width, m_width));
	m_tile.setFillColor(sf::Color::Black);
	m_tile.setOutlineThickness(1.0f);
	m_tile.setOutlineColor(sf::Color(sf::Color(0,255,0,150)));
}

void Tile::setPosition(float t_x, float t_y)
{
	m_tile.setPosition(t_x, t_y);
}

void Tile::render(sf::RenderWindow* t_window)
{
}

sf::Vector2f Tile::getPos()
{
	return m_tile.getPosition();
}

void Tile::clearLines()
{
	lines.clear();
}
void Tile::drawLines(sf::RenderWindow* t_window)
{
	t_window->draw(m_tile);
	// multiply by cell width
	if (m_integrationCost > 0 && m_integrationCost < 999 && showVectorField)
	{
		sf::Vector2f bestPathPosition = sf::Vector2f(static_cast<float>(m_vector.x) * 25, static_cast<float>(m_vector.y) * 25);
		lines.append(sf::Vertex{ m_tile.getPosition() + sf::Vector2f{25, 25} / 2.0f, sf::Color::Magenta });
		lines.append(sf::Vertex{ bestPathPosition + sf::Vector2f{ 25, 25 } / 2.0f, sf::Color(sf::Color(0,0,0,0)) });
		t_window->draw(lines);
	}
	if (showCost)
	{
		t_window->draw(m_text);
	}
}

void Tile::setColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
}