#pragma once

#include <vector>
#include <string>

#include "commands/command.h"

namespace text_editor {

	const int MAX_LINE_LENGTH = 256;

	class TextSpace {
	
	private:
		int _line_length = 64;
		std::vector<std::string> _text;
	public:
		const std::vector<std::string>& get_content() const { return _text; }
		
		void fit_lines();
		void apply_command_to_content(const Command& command);

		TextSpace() {}
		TextSpace(const std::vector<std::string>& text)
			: _text(text) { fit_lines(); }
		TextSpace(int line_length, const std::vector<std::string>& text)
			: _line_length(line_length), _text(text) { fit_lines(); }
	};
}
