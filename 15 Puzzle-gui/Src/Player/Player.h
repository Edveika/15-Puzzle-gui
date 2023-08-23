#pragma once
#include <memory>
#include <string>
#include <stdexcept>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "../Tile/Tile.h"
#include "../Board/Board.h"

class Player
{
private:
	enum MoveDirections
	{
		MOVE_DIRECTION_NONE,
		MOVE_DIRECTION_UP,
		MOVE_DIRECTION_DOWN,
		MOVE_DIRECTION_LEFT,
		MOVE_DIRECTION_RIGHT
	};

	std::shared_ptr<Board> m_board;
	std::shared_ptr<Tile> m_movable_tile;
	Coordinate m_new_movable_tile_coord;
	int m_move_count;

private:
	std::shared_ptr<Tile> get_new_movable_tile();
	std::shared_ptr<Tile> get_tile_by_mouse_coord(sf::Window& window, sf::Vector2i mouse_pos);
	std::shared_ptr<Tile> get_tile_from_mouse_coord_on_input(sf::Window& window, sf::Event& event);
	int get_move_direction_from_mouse_input(sf::Window& window, sf::Event& event);
	int get_move_direction_from_keyboard_input(sf::Event& event);

public:
	Player();

	void update_board();

	int get_move_count() { return m_move_count; }
	std::shared_ptr<Board> get_board() { if (m_board)return m_board; else return nullptr; }
	std::shared_ptr<Tile> get_movable_tile() { if (m_board->get_movable_tile()) return m_board->get_movable_tile(); else return nullptr; }

	bool set_move_direction_from_input(sf::Window& win, sf::Event& event);
};