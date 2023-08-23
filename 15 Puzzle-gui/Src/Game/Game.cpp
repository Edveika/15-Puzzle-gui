#include "Game.h"

Game::Game()
	: m_window{sf::VideoMode(800, 600), "15 Puzzle"}
{
	m_player = std::make_shared<Player>();
	if (!m_player)
		throw std::invalid_argument("m_player was nullptr");
	if (!m_player->get_board())
		throw std::invalid_argument("m_player->get_board() was nullptr");

	m_render = std::make_shared<Render>(m_player->get_board()->get_tiles(), 800, 600);
	if (!m_render)
		throw std::invalid_argument("m_render was nullptr");

	m_timer = std::make_shared<Timer>();
	if (!m_timer)
		throw std::invalid_argument("m_timer was nullptr");

	m_board = m_player->get_board();
	m_window.setKeyRepeatEnabled(false);
}

void Game::update(sf::Event& event)
{
	// Check for input & new move dicretion
	if (m_player->set_move_direction_from_input(m_window, event))
		// When we got out input, board will be updated and then rendered
		m_player->update_board();
}

void Game::render()
{
	m_render->render_board(m_window);
}

void Game::run()
{
	// Start the game loop
	while (m_window.isOpen())
	{
		// Process events
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				m_window.close();
			else if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed) && !victory_check())
				update(event);
		}
		// Clear screen
		m_window.clear();

		if (!victory_check())
		{
			render();
			m_timer->end();
		}
		else
		{
			m_render->render_victory_screen(m_window, m_player->get_move_count(), m_timer->get_time_elapsed());
		}

		// Update the window
		m_window.display();
	}
}

bool Game::victory_check()
{
	std::vector<std::shared_ptr<Tile>> board_tiles = m_player->get_board()->get_tiles();

	// Iterates though the vector and checks if all of the tile digits are in order
	// NOTE: size - 1 because we dont want to check our movable tile
	for (int i = 0; i < board_tiles.size() - 1; ++i)
	{
		if (!board_tiles[i])
			break;

		if (board_tiles[i]->get_digit() != i + 1)
			return false;
	}

	return true;
}