#include "Tile.h"

Tile::Tile()
{
	m_tile.setSize(sf::Vector2f(m_width, m_width));
	//m_tile.setOrigin(sf::Vector2f(m_width,m_width));
	m_tile.setFillColor(sf::Color::Black);
	m_tile.setOutlineThickness(1.0f);
	m_tile.setOutlineColor(sf::Color::Green);
}

void Tile::setPosition(float t_x, float t_y)
{
	m_tile.setPosition(t_x, t_y);
}

void Tile::render(sf::RenderWindow* t_window)
{
	t_window->draw(m_tile);
}

void Tile::setColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
}