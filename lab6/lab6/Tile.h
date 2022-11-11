#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "math.h"
#include <iostream>

class Tile
{
	private:

		sf::RectangleShape m_tile;

	public:
		sf::VertexArray lines{ sf::Lines };
		bool m_checked;
		sf::Text m_text;
		sf::Vector2i rowColumn{};
		sf::Vector2f m_vector{};
		sf::Vector2f getPos();

		void clearLines();
		void drawLines(sf::RenderWindow* t_window);

		float m_integrationCost;
		void setUpText(sf::Font& t_font);
		int alpha;
		sf::Vector2i pathPos{};
		int m_cost;
		Tile(sf::Font& t_font);
		float m_width = 20.0f;
		void setPosition(float m_x, float m_y);
		void render(sf::RenderWindow* t_window);
		void setColour(sf::Color t_color);
		void setColourIntensity();
		sf::RectangleShape getTile() { return m_tile; }
		bool showCost = false, showVectorField = false;
};
#endif // !TILE_HPP
