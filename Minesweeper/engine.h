#include "settings.h"
#include "window.h"
#include "board.h"
#include "button.h"
#include "message.h"

#pragma once
class engine
{
public:
	engine();
	void run_game();
	void init_map(std::vector<std::vector<int>>& game_map);

	sf::RenderWindow* get_window() { return game_window->window_; }
private:

	sf::Vector2i mouse_enter_in_button(sf::Vector2i mouse_pos);
	void mouse_left_click(sf::Vector2i mouse_pos);
	void mouse_right_click(sf::Vector2i mouse_pos);
	int get_index_with_mouse_position(sf::Vector2i& mouse_pos);
	
	void refresh_move(int m, int n);

	bool isValid(int row, int col);

	settings* game_settings;
	window* game_window;
	board* game_board;
	message* game_text;
	button* game_button;

	bool game_first_step = true;

	int founded_mine = 0;


};

