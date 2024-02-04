#pragma once

#include <string>
#include <vector>

#include "command.h"

namespace text_editor {

	class ReplaceSymbolData : public CommandExecutionData {
	
	private:
		char _value;
		int _index;
		int _position;
	public:
		char get_value() const { return _value; }
		int get_index() const { return _index; }
		int get_position() const { return _position; }

		ReplaceSymbolData(int index, int positon, char value) 
			: _index(index), _position(positon), _value(value) {}
	};

	class ReplaceSymbolCommand : public Command {

	private:
		const ReplaceSymbolData& _data;
	public:
		ReplaceSymbolCommand(const ReplaceSymbolData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			char symbol = _data.get_value();
			content[_data.get_index()][_data.get_position()] = _data.get_value();
		}
	};
}
