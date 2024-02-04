#pragma once

#include <string>

void replace_all_matches(
	std::string& content, 
	const std::string& to_find, 
	const std::string& to_replace
) {
    size_t pos = content.find(to_find);
    
    while (pos != std::string::npos) {
        content.replace(pos, to_find.size(), to_replace);
        pos = content.find(to_find, pos + to_replace.size());
    }
}
