#pragma once

#include <string>
#include <vector>

#include "command.h"

namespace text_editor {

	class InsertManyLinesData : public CommandExecutionData {

	private: 
		int _start_index;
		std::vector<std::string> _lines;
	public:
		int get_start_index() const { return _start_index; }
		const std::vector<std::string>& get_lines() const { return _lines; }

		InsertManyLinesData(int index, const std::vector<std::string>& lines)
			: _start_index(index), _lines(lines) {}
	};

	class InsertManyLinesCommand : public Command {

	private: 
		const InsertManyLinesData& _data;
	public:
		InsertManyLinesCommand(const InsertManyLinesData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			int size = _data.get_lines().size();
			
			for (int i = 0; i < size; i++) {
				content.insert(
					content.begin() + _data.get_start_index() + i, _data.get_lines()[i]);
			}
		}
	};
}
