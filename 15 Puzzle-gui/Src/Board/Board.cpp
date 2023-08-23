#include "Board.h"

Board::Board()
{
	m_width = 4;
	m_height = 4;
	create_tiles(16);
	randomize_tile_digits();
}

int Board::get_tile_index(const Coordinate coord)
{
	for (int i = 0; i < m_tiles.size(); ++i)
	{
		std::shared_ptr<Tile> i_tile = m_tiles[i];

		if (!i_tile)
			break;

		int i_tile_pos_x = i_tile->get_coord().x;
		int i_tile_pos_y = i_tile->get_coord().y;

		if (i_tile_pos_x == coord.x && i_tile_pos_y == coord.y)
			return i;
	}

	return INDEX_ERROR_TILE_NOT_FOUND;
}

void Board::create_tiles(int tile_count)
{
	int pos_x = 0;
	int pos_y = 0;

	// Fills empty tiles with numbers except for the last one
	// Starts from number 1 because number 0 is reserved for the movable tile
	for (int i = 1; i < tile_count; ++i)
	{
		if (pos_x + 1 > m_width)
		{
			pos_x = 0;
			++pos_y;
		}

		std::shared_ptr<Tile> i_tile = std::make_shared<Tile>(Coordinate{ pos_x, pos_y }, i);

		if (!i_tile)
			break;

		m_tiles.push_back(i_tile);
		++pos_x;
	}

	// Creates the movable tile with digit 0
	std::shared_ptr<Tile> movable_tile = std::make_shared<Tile>(Coordinate{ pos_x, pos_y }, 0);

	if (!movable_tile)
		return;

	m_tiles.push_back(movable_tile);
	m_movable_tile = m_tiles[m_tiles.size() - 1];
}

void Board::randomize_tile_digits()
{
	// Iterates through the tiles vector
	for (int i = 0; i < m_tiles.size(); ++i)
	{
		// Picks a random index
		int random_index = rand() % m_tiles.size();

		if (!(m_tiles[i] || m_tiles[random_index]))
			break;

		// When movable tile's digit is changed, sets it to point to that object that has its digit
		if (m_tiles[i] == m_movable_tile)
		{
			m_movable_tile = m_tiles[random_index];
		}
		else if (m_tiles[random_index] == m_movable_tile)
		{
			m_movable_tile = m_tiles[i];
		}

		// And swaps the DIGITS between i and random_index tiles
		std::swap(m_tiles[i]->get_digit_ref(), m_tiles[random_index]->get_digit_ref());
	}
}