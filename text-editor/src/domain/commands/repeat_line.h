#pragma once

#include <vector>
#include <string>

#include "command.h"

namespace text_editor {
	
	class RepeatLineData : public CommandExecutionData {

	private:
		int _index;
		int _times;
		std::string _line;
	public:
		int get_index() const { return _index; }
		int get_times() const { return _times; }
		std::string get_line() const { return _line; }

		RepeatLineData(int index, int times, std::string line)
			: _index(index), _times(times), _line(line) {}
	};

	class RepeatLineCommand : public Command {

	private:
		const RepeatLineData& _data;
	public:
		RepeatLineCommand(const RepeatLineData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			for (int i = 0; i < _data.get_times(); i++) {
				content.insert(content.begin() + _data.get_index(), _data.get_line());
			}
		}
	};
}
