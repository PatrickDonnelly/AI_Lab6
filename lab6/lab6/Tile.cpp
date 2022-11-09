#include "Tile.h"

void Tile::setUpText(sf::Font& t_font)
{
	m_text.setFont(t_font);
	m_text.setString("0");
	m_text.setPosition(12.5f, 12.5f);
	//m_text.setOrigin(-12.5f,-12.5f);
	m_text.setCharacterSize(16U);
	m_text.setFillColor(sf::Color::White);
}

Tile::Tile(sf::Font& t_font)
{
	setUpText(t_font);
	m_checked = false;
	m_cost = 0;
	m_integrationCost = 0.0f;
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
	t_window->draw(m_text);
}

void Tile::setColour(sf::Color t_color)
{
	m_tile.setFillColor(t_color);
}