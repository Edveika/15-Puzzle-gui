#include "SfTile.h"

SfTile::SfTile(std::shared_ptr<Tile> tile, sf::Vector2f coord, sf::Vector2f tile_size)
{
	m_tile = tile;
	if (!m_tile)
		throw std::invalid_argument("m_tile was nullptr");

	m_rect = sf::RectangleShape(tile_size);
	m_rect.setPosition(coord);
	m_rect.setFillColor(sf::Color(0, 0, 0));
}