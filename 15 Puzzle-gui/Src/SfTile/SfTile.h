#pragma once
#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "../Tile/Tile.h"

class SfTile
{
private:
	std::shared_ptr<Tile> m_tile;
	sf::RectangleShape m_rect;
	sf::Text m_tile_digit;

public:
	SfTile(std::shared_ptr<Tile> tile, sf::Vector2f coord, sf::Vector2f tile_size);

	sf::RectangleShape get_tile_background() { return m_rect; }
	sf::Text& get_tile_digit() { return m_tile_digit; }
	std::shared_ptr<Tile> get_tile() { return m_tile; }
};