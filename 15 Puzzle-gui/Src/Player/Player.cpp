#include "Player.h"

Player::Player()
{
	m_board = std::make_shared<Board>();
	if (!m_board)
		throw std::invalid_argument("m_board was nullptr");

	m_movable_tile = m_board->get_movable_tile();
	if (!m_movable_tile)
		throw std::invalid_argument("m_movable_tile was nullptr");

	m_move_count = 0;
	m_new_movable_tile_coord = m_movable_tile->get_coord();
}

bool mouse_in_window_bounds(sf::Vector2i mouse_pos, sf::Vector2u win_size)
{
	if (mouse_pos.x <= win_size.x && mouse_pos.x >= 0)
	{
		if (mouse_pos.y <= win_size.y && mouse_pos.y >= 0)
		{
			return true;
		}
	}

	return false;
}

bool mouse_in_tile_bounds(std::shared_ptr<Tile>& tile, sf::Vector2i mouse_pos, sf::Vector2f rect_size)
{
	float pos_x = tile->get_coord().x;
	float pos_y = tile->get_coord().y;
	sf::Vector2f top_left { pos_x* rect_size.x, pos_y* rect_size.y };
	sf::Vector2f bottom_right { top_left.x + rect_size.x, top_left.y + rect_size.y };

	if (mouse_pos.x >= top_left.x && mouse_pos.x <= bottom_right.x)
	{
		if (mouse_pos.y <= bottom_right.y && mouse_pos.y >= top_left.y)
		{
			return true;
		}
	}

	return false;
}

std::shared_ptr<Tile> Player::get_tile_by_mouse_coord(sf::Window& window, sf::Vector2i mouse_pos)
{
	const std::vector<std::shared_ptr<Tile>> tile_list = m_board->get_tiles();

	for (int i = 0; i < tile_list.size(); ++i)
	{
		std::shared_ptr<Tile> i_tile = tile_list[i];

		if (mouse_in_window_bounds(mouse_pos, window.getSize()))
		{
			sf::Vector2f rect_size = { window.getSize().x / 4.0f, window.getSize().y / 4.0f };

			if (mouse_in_tile_bounds(i_tile, mouse_pos, rect_size))
			{
				return i_tile;
			}
		}
	}

	return nullptr;
}

std::shared_ptr<Tile> Player::get_tile_from_mouse_coord_on_input(sf::Window& window, sf::Event& event)
{
	sf::Vector2i mouse_coord;
	if (event.mouseButton.button == sf::Mouse::Left)
		mouse_coord = sf::Mouse::getPosition(window);
	else
		return nullptr;

	return get_tile_by_mouse_coord(window, mouse_coord);
}

int Player::get_move_direction_from_mouse_input(sf::Window& window, sf::Event& event)
{
	int move_direction = MOVE_DIRECTION_NONE;
	std::shared_ptr<Tile> selected_tile = get_tile_from_mouse_coord_on_input(window, event);

	if (!selected_tile || !m_movable_tile)
		return move_direction;

	Coordinate selected_coord = selected_tile->get_coord();
	Coordinate cur_coordinate = m_movable_tile->get_coord();

	if (selected_coord.x == cur_coordinate.x + 1 && selected_coord.y == cur_coordinate.y)
		move_direction = MOVE_DIRECTION_RIGHT;
	else if (selected_coord.x == cur_coordinate.x - 1 && selected_coord.y == cur_coordinate.y)
		move_direction = MOVE_DIRECTION_LEFT;
	else if (selected_coord.y == cur_coordinate.y + 1 && selected_coord.x == cur_coordinate.x)
		move_direction = MOVE_DIRECTION_DOWN;
	else if (selected_coord.y == cur_coordinate.y - 1 && selected_coord.x == cur_coordinate.x)
		move_direction = MOVE_DIRECTION_UP;

	return move_direction;
}

int Player::get_move_direction_from_keyboard_input(sf::Event& event)
{
	int move_direction = MOVE_DIRECTION_NONE;

	if (event.key.scancode == sf::Keyboard::Scan::W || event.key.scancode == sf::Keyboard::Scan::Up)
		move_direction = MOVE_DIRECTION_UP;
	else if (event.key.scancode == sf::Keyboard::Scan::S || event.key.scancode == sf::Keyboard::Scan::Down)
		move_direction = MOVE_DIRECTION_DOWN;
	else if (event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::Left)
		move_direction = MOVE_DIRECTION_LEFT;
	else if (event.key.scancode == sf::Keyboard::Scan::D || event.key.scancode == sf::Keyboard::Scan::Right)
		move_direction = MOVE_DIRECTION_RIGHT;

	return move_direction;
}

bool Player::set_move_direction_from_input(sf::Window& win, sf::Event& event)
{
	int move_direction = MOVE_DIRECTION_NONE;
	if (event.type == sf::Event::MouseButtonPressed)
		move_direction = get_move_direction_from_mouse_input(win, event);
	else if (event.type == sf::Event::KeyPressed)
		move_direction = get_move_direction_from_keyboard_input(event);

	if (move_direction != MOVE_DIRECTION_NONE)
	{
		if (move_direction == MOVE_DIRECTION_UP)
		{
			if (m_new_movable_tile_coord.y - 1 >= 0)
			{
				m_new_movable_tile_coord.y -= 1;
				return true;
			}
		}
		else if (move_direction == MOVE_DIRECTION_DOWN)
		{
			if (m_new_movable_tile_coord.y + 1 < m_board->get_height())
			{
				m_new_movable_tile_coord.y += 1;
				return true;
			}
		}
		else if (move_direction == MOVE_DIRECTION_LEFT)
		{
			if (m_new_movable_tile_coord.x - 1 >= 0)
			{
				m_new_movable_tile_coord.x -= 1;
				return true;
			}
		}
		else if (move_direction == MOVE_DIRECTION_RIGHT)
		{
			if (m_new_movable_tile_coord.x + 1 < m_board->get_width())
			{
				m_new_movable_tile_coord.x += 1;
				return true;
			}
		}
	}

	return false;
}

std::shared_ptr<Tile> Player::get_new_movable_tile()
{
	// Finds new tile for the movable tile after it its position has changed
	int i_new = m_board->get_tile_index(m_new_movable_tile_coord);

	if (!m_board || i_new == Board::INDEX_ERROR_TILE_NOT_FOUND || !m_board->get_tiles()[i_new])
		return nullptr;

	return m_board->get_tiles()[i_new];
}

void Player::update_board()
{
	std::shared_ptr<Tile> new_movable_tile = get_new_movable_tile();
	std::shared_ptr<Tile> old_movable_tile = m_board->get_movable_tile();

	if (!(new_movable_tile || old_movable_tile))
		return;

	// Sets new movable tile ptr to point to the tile in new movable tile's position
	m_board->set_movable_tile(new_movable_tile);
	m_movable_tile = new_movable_tile;

	// Swaps digits of old movable tile and new movable tile
	std::swap(old_movable_tile->get_digit_ref(), new_movable_tile->get_digit_ref());

	// This keeps track of how many moves in total were made
	++m_move_count;
}