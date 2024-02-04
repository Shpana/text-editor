#pragma once

#include <algorithm>

void clamp_value(int& value, int min, int max) {
	value = std::max(min, std::min(max, value));
}
