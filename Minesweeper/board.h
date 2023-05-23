#include <SFML/Graphics.hpp>

#pragma once
class board
{
public:
	board(int h_c, int v_c, sf::RenderWindow& game_wind);
	sf::VertexArray get_board_lines() { return lines; }

private:
	sf::VertexArray lines;

	int hrz_count = 0;
	int vrt_count = 0;
};