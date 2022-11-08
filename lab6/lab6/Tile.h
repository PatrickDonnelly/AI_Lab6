#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>

class Tile
{
	private:

		sf::RectangleShape m_tile;

	public:

		Tile();
		float m_width = 32.0f;
		void setPosition(float m_x, float m_y);
		void render(sf::RenderWindow* t_window);

};
#endif // !TILE_HPP
