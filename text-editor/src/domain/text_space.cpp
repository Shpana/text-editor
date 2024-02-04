#include "text_space.h"

#include <iostream>

namespace text_editor {
	
	void TextSpace::apply_command_to_content(const Command& command) {
		command.apply_to(_text);
		fit_lines();
	}	

	void TextSpace::fit_lines() {
		for (int i = 0; i < _text.size(); i++) {
			std::string line = _text[i];

			if (line.length() > _line_length) {
				std::string fitted_line = line.substr(0, _line_length);
				_text[i] = fitted_line;
				_text.insert(_text.begin() + i + 1, line.substr(_line_length));
			}
		}
	}
}
