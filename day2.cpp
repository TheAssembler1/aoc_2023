#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <cassert>

struct Session {
	std::optional<int> r = std::nullopt;
	std::optional<int> g = std::nullopt;
	std::optional<int> b = std::nullopt;
};

void print_session(Session s) {
	if(s.r.has_value()) {
		std::cout << "r: " << s.r.value() << std::endl;
	}
	if(s.g.has_value()) {
		std::cout << "g: " << s.g.value() << std::endl;
	}
	if(s.b.has_value()) {
		std::cout << "b: " << s.b.value() << std::endl;
	}
}

std::vector<std::vector<Session>> games{};

int main() {
	std::ifstream input{"/home/ta1/src/aoc_2023/in.txt", std::ifstream::in};
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s, '\n'); lines.push_back(s));
	int total = 0;
	int cur_num;

	for(int i = 0; i < lines.size(); i++) {
		games.push_back({});
	}

	int gameid = 0;
	for(const std::string& s: lines) {
		std::cout << s << std::endl;

		int cur_index = 0;
		while(s[cur_index] != ':') cur_index++;
		cur_index++;
		int cur_session = 0;
		for(; cur_index < s.size(); cur_index++) {
			while(s[cur_index] == ' ') cur_index++;

			std::string num{};
			while(std::isdigit(s[cur_index])) {
				num.push_back(s[cur_index]);
				cur_index++;
			}

			assert(num.size() > 0);

			cur_num = std::stoi(num);

			while(s[cur_index] == ' ') cur_index++;

			std::string color{};
			while(cur_index < s.size() && !std::isdigit(s[cur_index]) && s[cur_index] != ' ') {
				color.push_back(s[cur_index]);
				cur_index++;
			}

			assert(color.size() > 0);

			bool n = false;

			if(color.back() == ';') {
				n = true;
			}

			if(color.back() == ';' || color.back() == ',') {
				color.pop_back();
			}

			if(cur_session >= games[gameid].size()) {
				games[gameid].push_back({});
			}

			if(color == "red") {
				games[gameid][cur_session].r = cur_num;
			} else if (color == "blue") {
				games[gameid][cur_session].b = cur_num;
			} else if (color == "green") {
				games[gameid][cur_session].g = cur_num;
			} else {
				assert(0);
			}

			if(n) cur_session++;
		}

		gameid++;
	}

	int cur_game = 1;
	for(auto g: games) {
		bool possible = true;

		int red_min = 0;
		int blue_min = 0;
		int green_min = 0;

		for(auto s: g) {
			assert(s.r.has_value() || s.g.has_value() || s.b.has_value());
			print_session(s);
			std::cout << std::endl;

			if(s.r.has_value()) {
				red_min = std::max(red_min, s.r.value());
			}
			if(s.g.has_value()) {
				green_min = std::max(green_min, s.g.value());
			}
			if(s.b.has_value()) {
				blue_min = std::max(blue_min, s.b.value());
			}
		}

		total += (red_min * blue_min * green_min);

		std::cout << "==============================" << std::endl;
		cur_game++;
	}

	std::cout << "total: " << total;

	return total;
}
