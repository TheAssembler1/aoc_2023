#include <iostream>
#include <fstream>
#include <vector>
#include <optional>

int main() {
	std::ifstream input{"/home/ta1/src/aoc_2023/in.txt", std::ifstream::in};
	std::vector<std::string> lines{};
	for (std::string s; std::getline(input, s, '\n'); lines.push_back(s));
	int total = 0;

	for(const std::string& s: lines) {
		int left = 0;
		int right = s.size() - 1;

		while(left <= right) {
			char l = s[left];
			char r = s[right];

			if(left == right) {
				total += std::stoi(std::string{l} + std::string{r});
				break;
			}
			if(l >= '0' && l <= '9' && r >= '0' && r <= '9') {
				total += std::stoi(std::string{l} + std::string{r});
				break;
			}

			if(l < '0' || l > '9') left++;
			if(r < '0' || r > '9') right--;
		}
	}

	std::cout << total;

	return total;
}
