#pragma once
#include <vector>
#include <cmath>
#include <memory>
#include <cassert>
#include <utility>

#include "../Tile/Tile.h"

class Board
{
public:
	enum TileIndexError
	{
		INDEX_ERROR_TILE_NOT_FOUND = -1
	};

private:
	std::vector<std::shared_ptr<Tile>> m_tiles;
	std::shared_ptr<Tile> m_movable_tile;
	int m_width;
	int m_height;

private:
	void create_tiles(int tile_count);
	void randomize_tile_digits();

public:
	Board();

	// Getters
	int get_tile_index(const Coordinate coord);
	std::vector<std::shared_ptr<Tile>>& get_tiles() { return m_tiles; }
	std::shared_ptr<Tile> get_movable_tile() { return m_movable_tile; }
	int get_width() { return m_width; }
	int get_height() { return m_height; }

	// Setters
	void set_movable_tile(std::shared_ptr<Tile> new_tile) { m_movable_tile = new_tile; }
};