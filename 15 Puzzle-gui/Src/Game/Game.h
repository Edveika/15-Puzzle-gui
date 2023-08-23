#pragma once
#include <memory>
#include <vector>
#include <utility>
#include <stdexcept>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "../Tile/Tile.h"
#include "../Board/Board.h"
#include "../Render/Render.h"
#include "../Player/Player.h"
#include "../Timer/Timer.h"

class Game
{
private:
	std::shared_ptr<Render> m_render;
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Board> m_board;
	std::shared_ptr<Timer> m_timer;
	sf::RenderWindow m_window;

private:
	bool victory_check();
	void update(sf::Event& event);
	void render();

public:
	Game();

	void run();
};