#pragma once

#include <string>

bool is_increasing_digit_subsequence(const std::string& subsequence) {
	bool state = true;
	char max_digit = '0' - 1;

	for (auto symbol : subsequence) {
		if (symbol - max_digit <= 0) {
			state = false;
			break;
		}
		max_digit = symbol;
	}
	return state;
}
