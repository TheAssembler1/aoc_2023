#include <iostream>
#include <fstream>
#include <vector>
#include <optional>
#include <vector>

std::vector<std::string> nums = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
std::optional<char> search_string(const std::string& str, int index) {
	std::string s{};
	while(index < str.size() && !std::isdigit(str[index])) {
		s.push_back(str[index]);

		int i = 0;
		for(auto e: nums) {
			if(s == e) {
				return '0' + 1 + i;
			}
			i++;
		}

		index++;
	}

	return std::nullopt;
}

int main() {
	std::ifstream input{"/home/ta1/src/aoc_2023/in.txt", std::ifstream::in};
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s, '\n'); lines.push_back(s));
	int total = 0;

	for(const std::string& s: lines) {
		char lchar = 0;
		char rchar = 0;
		std::cout << s << ": ";

		for(int i = 0; i < s.size(); i++) {
			if(std::isdigit(s[i])) {
				if(!lchar) {
					lchar = s[i];
				} else {
					rchar = s[i];
				}
			} else if(search_string(s, i).has_value()) {
				if(!lchar) {
					lchar = search_string(s, i).value();
				} else {
					rchar = search_string(s, i).value();
				}
			}
		}
	}

	std::cout << "Total: " << total << std::endl;
}
