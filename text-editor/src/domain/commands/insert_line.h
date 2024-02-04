#pragma once

#include <string>
#include <vector>

#include "command.h"

namespace text_editor {

	class InstertLineData : public CommandExecutionData {

	private:
		int _index;
		std::string _line;
	public:
		int get_index() const { return _index; }
		std::string get_line() const { return _line; }

		InstertLineData(int index, const std::string& line)
			: _index(index), _line(line) {}
	};

	class InsertLineCommand : public Command {

	private:
		const InstertLineData& _data;
	public:
		InsertLineCommand(const InstertLineData& data)
			: _data(data) {}
		
		virtual void apply_to(std::vector<std::string>& content) const {
			content.insert(content.begin() + _data.get_index(), _data.get_line());
		}
	};
}
