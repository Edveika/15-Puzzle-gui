#include "Render.h"

Render::Render(std::vector<std::shared_ptr<Tile>>& tile_list, int screen_width, int screen_height)
{
	m_font.loadFromFile("ARIAL.TTF"); // font doesnt get copied so we cant create it inside the sfTile class
	create_sf_tiles(tile_list, screen_width, screen_height);
}

bool Render::create_sf_tiles(std::vector<std::shared_ptr<Tile>> tile_list, int screen_width, int screen_height)
{
	for (int i = 0; i < tile_list.size(); ++i)
	{
		std::shared_ptr<Tile> i_tile = tile_list[i];
		sf::Vector2f new_tile_coord = sf::Vector2f(i_tile->get_coord().x * (screen_width / 4.0f), i_tile->get_coord().y * (screen_height / 4.0f));
		sf::Vector2f new_tile_size = sf::Vector2f(screen_width / 4.0f, screen_height / 4.0f);
		SfTile new_sf_tile = SfTile(i_tile, new_tile_coord, new_tile_size);

		new_sf_tile.get_tile_digit().setString(std::to_string(i_tile->get_digit()));
		new_sf_tile.get_tile_digit().setFont(m_font);
		new_sf_tile.get_tile_digit().setOrigin(new_sf_tile.get_tile_digit().getGlobalBounds().getSize() / 2.f + new_sf_tile.get_tile_digit().getLocalBounds().getPosition());
		new_sf_tile.get_tile_digit().setPosition(new_sf_tile.get_tile_background().getPosition() + (new_sf_tile.get_tile_background().getSize() / 2.f));

		m_sf_tile_list.push_back(std::make_shared<SfTile>(new_sf_tile));

		if (!(i_tile || m_sf_tile_list[i]))
			return false;
	}

	return true;
}

std::string digit_to_str(int digit)
{
	std::string str;

	if (digit == 0)
		str = " ";
	else
		str = std::to_string(digit);

	return str;
}

void Render::render_board(sf::RenderWindow& window)
{
	for (int i = 0; i < m_sf_tile_list.size(); ++i)
	{
		std::shared_ptr<SfTile> i_sf_tile = m_sf_tile_list[i];
		int i_digit = i_sf_tile->get_tile()->get_digit();
		std::string str = digit_to_str(i_digit);

		i_sf_tile->get_tile_digit().setString(str); // updates the digit of the sfTile class

		window.draw(i_sf_tile->get_tile_background());
		window.draw(i_sf_tile->get_tile_digit());
	}
}

void center_text(sf::RenderWindow& window, sf::Text& text)
{
	auto center = text.getGlobalBounds().getSize() / 2.f;
	auto localBounds = center + text.getLocalBounds().getPosition();
	text.setOrigin(localBounds);
	text.setPosition(sf::Vector2f{ window.getSize() / 2u });
}

void Render::render_victory_screen(sf::RenderWindow& window, int move_count, double time_passed)
{
	sf::Text congrats = sf::Text("Congratulations, you have WON!!!", m_font, 30);
	center_text(window, congrats);

	sf::Text moves_made = sf::Text("Moves: " + std::to_string(move_count), m_font, 18);
	center_text(window, moves_made);
	moves_made.setPosition({ moves_made.getPosition().x, moves_made.getPosition().y + congrats.getCharacterSize() });

	std::ostringstream ss;
	ss << std::setprecision(1) << std::fixed << time_passed;
	sf::Text time_elapsed = sf::Text("Time elapsed: " + ss.str() + " seconds", m_font, 18);
	center_text(window, time_elapsed);
	time_elapsed.setPosition({ time_elapsed.getPosition().x, moves_made.getPosition().y + moves_made.getCharacterSize() });

	window.draw(congrats);
	window.draw(moves_made);
	window.draw(time_elapsed);
}