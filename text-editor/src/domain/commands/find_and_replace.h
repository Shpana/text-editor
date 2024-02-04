#pragma once

#include <string>
#include <vector>

#include "command.h"
#include "utils/replace_all_mathces.h"

namespace text_editor {

	class FindAndReplaceData : public CommandExecutionData {
	
	private:
		int _start;
		int _end;
		std::string _to_find;
		std::string _to_replace;
	public:
		int get_start() const { return _start; }
		int get_end() const { return _end; }
		std::string get_word_to_find() const { return _to_find; }
		std::string get_word_to_replace() const { return _to_replace; }

		FindAndReplaceData(
			int start, int end, std::string to_find, std::string to_replace)
			: _start(start), _end(end), _to_find(to_find), _to_replace(to_replace) {}
	};

	class FindAndReplaceCommand : public Command {

	private:
		const FindAndReplaceData& _data;
	public:
		FindAndReplaceCommand(const FindAndReplaceData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			for (int i = _data.get_start() - 1; i < _data.get_end(); i++) {
				replace_all_matches(
					content[i], _data.get_word_to_find(), _data.get_word_to_replace());
			}
		}
	};
}
