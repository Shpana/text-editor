#pragma once

#include <string>
#include <vector>

#include "command.h"

namespace text_editor {

	class InsertSubstringData : public CommandExecutionData {

	private:
		int _index;
		int _position;
		std::string _subline;
	public:
		int get_index() const { return _index; }
		int get_position() const { return _position; }
		std::string get_subline() const { return _subline; }

		InsertSubstringData(int index, int position, std::string subline)
			: _index(index), _position(position), _subline(subline) {}
	};

	class InsertSubstringCommand : public Command {
	
	private: 
		const InsertSubstringData& _data;
	public:
		InsertSubstringCommand(const InsertSubstringData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			content[_data.get_index()].insert(_data.get_position(), _data.get_subline());
		}
	};
}
