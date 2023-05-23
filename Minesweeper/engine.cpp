#include "engine.h"
#include <iostream>

engine::engine() {
	game_settings = new settings();
	game_window = new window(game_settings->get_game_heigth(), game_settings->get_game_width(), game_settings->get_game_name());
	game_board = new board(game_settings->get_game_board_hrz_count(), game_settings->get_game_board_vrt_count(), *game_window->window_);
	game_button = new button(game_settings->get_game_width(), game_settings->get_game_heigth() - 40, game_settings->get_game_board_hrz_count(), game_settings->get_game_board_vrt_count());
	game_text = new message(sf::Vector2f(15, game_settings->get_game_heigth() - 37));
}

void engine::init_map(std::vector<std::vector<int>>& draw_map) {
	for (int m = 0; m < draw_map.size(); m++) {
		for (int n = 0; n < draw_map[m].size(); n++) {
			game_window->window_->draw(game_button->get_button(sf::Vector2f(n * game_button->get_button_size().x, m * game_button->get_button_size().y), draw_map[m][n]));
		}
	}
}

sf::Vector2i engine::mouse_enter_in_button(sf::Vector2i mouse_pos) {
	int tmp_col, tmp_row;
	tmp_row = mouse_pos.y / (game_settings->get_game_width() / game_settings->get_game_board_hrz_count());
	tmp_col = mouse_pos.x / ((game_settings->get_game_heigth() - 40) / game_settings->get_game_board_vrt_count());
	return sf::Vector2i(tmp_col, tmp_row);
}

int engine::get_index_with_mouse_position(sf::Vector2i& mouse_pos) {
	int tmp_col, tmp_row;
	tmp_row = mouse_pos.y / (game_settings->get_game_width() / game_settings->get_game_board_hrz_count());
	tmp_col = mouse_pos.x / (game_settings->get_game_heigth() / game_settings->get_game_board_vrt_count());
	return tmp_col + tmp_row * (game_settings->get_game_heigth() / game_settings->get_game_board_vrt_count());
}

bool engine::isValid(int row, int col)
{
	return (row >= 0) && (row < game_settings->get_game_board_vrt_count()) && (col >= 0) && (col < game_settings->get_game_board_hrz_count());
}

void engine::mouse_right_click(sf::Vector2i mouse_pos) {
	if (mouse_pos.x > game_settings->get_game_width() or mouse_pos.x < 0 or mouse_pos.y > game_settings->get_game_heigth() - 40 or mouse_pos.y < 0)
		return;
	if (game_settings->get_draw_map()[mouse_pos.y][mouse_pos.x] == 0) {
		game_settings->set_game_array_value(mouse_pos.y, mouse_pos.x, 10);
		if (game_settings->get_game_map()[mouse_pos.y][mouse_pos.x] == 11) {
			founded_mine++;
			std::string msg = "We have ";
			msg += std::to_string(game_settings->get_mine_map().size());
			msg += " mines. Founded ";
			msg += std::to_string(founded_mine);
			game_text->set_text(msg);
		}
	}
	else if (game_settings->get_draw_map()[mouse_pos.y][mouse_pos.x] == 10) {
		game_settings->set_game_array_value(mouse_pos.y, mouse_pos.x, 0);
		if (game_settings->get_game_map()[mouse_pos.y][mouse_pos.x] == 11) {
			founded_mine--;
			std::string msg = "We have ";
			msg += std::to_string(game_settings->get_mine_map().size());
			msg += " mines. Founded ";
			msg += std::to_string(founded_mine);
			game_text->set_text(msg);
		}
	}
	if (founded_mine == game_settings->get_mine_map().size()) {
		game_text->set_text("!!!Congratulations.You won !!!");
		return;
	}
}

void engine::refresh_move(int m, int n) {

	if (isValid(m, n)) {
		if (game_settings->get_game_map()[m][n] == 11)
			return;
	}
	if (isValid(m - 1, n)) {
		if (game_settings->get_draw_map()[m - 1][n] == 0 && game_settings->get_game_map()[m - 1][n] != 11) {
			game_settings->set_game_array_value(m - 1, n, game_settings->get_game_map()[m - 1][n]);
			refresh_move(m - 1, n);
		}
	}
	if (isValid(m, n - 1)) {
		if (game_settings->get_draw_map()[m][n - 1] == 0 && game_settings->get_game_map()[m][n - 1] != 11) {
			game_settings->set_game_array_value(m, n - 1, game_settings->get_game_map()[m][n - 1]);
			refresh_move(m, n - 1);
		}
	}
	if (isValid(m, n)) {
		if (game_settings->get_draw_map()[m][n] == 0 && game_settings->get_game_map()[m][n] != 11) {
			game_settings->set_game_array_value(m, n, game_settings->get_game_map()[m][n]);
		}
	}
	if (isValid(m, n + 1)) {
		if (game_settings->get_draw_map()[m][n + 1] == 0 && game_settings->get_game_map()[m][n + 1] != 11) {
			game_settings->set_game_array_value(m, n + 1, game_settings->get_game_map()[m][n + 1]);
			refresh_move(m, n + 1);
		}
	}
	if (isValid(m + 1, n)) {
		if (game_settings->get_draw_map()[m + 1][n] == 0 && game_settings->get_game_map()[m + 1][n] != 11) {
			game_settings->set_game_array_value(m + 1, n, game_settings->get_game_map()[m + 1][n]);
			refresh_move(m + 1, n);
		}
	}
}

void engine::mouse_left_click(sf::Vector2i mouse_pos) {

	int m = mouse_pos.y;
	int n = mouse_pos.x;

	if (game_settings->get_draw_map()[m][n] == 10)
		return;

	std::string msg = "We have ";
	msg += std::to_string(game_settings->get_mine_map().size());
	msg += " mines";
	game_text->set_text(msg);
	game_first_step = false;

	if (game_settings->get_game_map()[m][n] == 11) {
		game_text->set_text("So sorry, you lost");
		for (auto& it : game_settings->get_mine_map()) {
			int m_ = it / game_settings->get_game_board_hrz_count();
			int n_ = it - m_ * game_settings->get_game_board_hrz_count();
			game_settings->set_game_array_value(m_, n_, 11);
		}
		return;
	}
	refresh_move(m, n);

}

void engine::run_game() {
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	while (game_window->window_->isOpen())
	{
		sf::Event event;
		while (game_window->window_->pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::getPosition(*game_window->window_).x > game_settings->get_game_width()
					|| sf::Mouse::getPosition(*game_window->window_).x < 0
					|| sf::Mouse::getPosition(*game_window->window_).y > game_settings->get_game_heigth() - 40
					|| sf::Mouse::getPosition(*game_window->window_).x < 0)
					break;
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					mouse_left_click(mouse_enter_in_button(sf::Mouse::getPosition(*game_window->window_)));
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
				{
					if (!game_first_step) {
						game_first_step = false;
						mouse_right_click(mouse_enter_in_button(sf::Mouse::getPosition(*game_window->window_)));
					}
				}
			}
			if (event.type == sf::Event::Closed)
				game_window->window_->close();
		}

		game_window->window_->clear();
		init_map(game_settings->get_draw_map());
		game_window->window_->draw(game_text->get_text());
		game_window->window_->display();
	}
}