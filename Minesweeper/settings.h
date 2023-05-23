#include <string>
#include <vector>
#pragma once
class settings
{
public:
	settings();
	const std::string get_game_name() { return game_name; }
	int get_game_heigth() { return game_heigth; }
	int get_game_width() { return game_width; }
	int get_game_board_hrz_count() { return horizonical_count; }
	int get_game_board_vrt_count() { return vertical_count; }
	std::vector<int>& get_mine_map() { return mine_map; }

	void set_game_array_value(int m, int n, int value);

	std::vector<std::vector<int>>& get_game_map() { return game_array; }
	std::vector<std::vector<int>>& get_draw_map() { return draw_array; }

private:
	// game window parameters
	std::string game_name = "";
	int game_heigth = 0;
	int game_width = 0;

	// game drawing board parameters
	int horizonical_count = 0;
	int vertical_count = 0;

	void init_game_array();
	void generate_game_map();

	bool isValid_(int row, int col);

	std::vector<std::vector<int>> game_array;
	std::vector<std::vector<int>> draw_array;
	std::vector<int> mine_map;
};

