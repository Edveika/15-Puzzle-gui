#pragma once
#include <memory>
#include <vector>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>

#include "../Tile/Tile.h"
#include "../SfTile/SfTile.h"

class Render
{
private:
	std::vector<std::shared_ptr<SfTile>> m_sf_tile_list;
	sf::Font m_font;

private:
	bool create_sf_tiles(std::vector<std::shared_ptr<Tile>> tile_list, int screen_width, int screen_height);

public:
	Render(std::vector<std::shared_ptr<Tile>>& tile_list, int screen_width, int screen_height);

	void render_board(sf::RenderWindow& window);
	void render_victory_screen(sf::RenderWindow& window, int move_count, double time_passed);
};