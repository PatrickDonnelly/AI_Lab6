#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{
	private:

		sf::RectangleShape m_tile;

	public:

		bool m_checked;
		sf::Text m_text;
		sf::Vector2i rowColumn{};
		float m_integrationCost;
		void setUpText(sf::Font& t_font);

		int m_cost;
		Tile(sf::Font& t_font);
		float m_width = 25.0f;
		void setPosition(float m_x, float m_y);
		void render(sf::RenderWindow* t_window);
		void setColour(sf::Color t_color);
		sf::RectangleShape getTile() { return m_tile; }

};
#endif // !TILE_HPP
