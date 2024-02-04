#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "command.h"

namespace text_editor {

	class RemoveContentInBracesData : public CommandExecutionData {
		
	private:
		int _index;
	public:
		int get_index() const { return _index; }

		RemoveContentInBracesData(int index)
			: _index(index) {}
	};

	class RemoveContentInBracesCommand : public Command {

	private:
		const RemoveContentInBracesData& _data;
	public:
		RemoveContentInBracesCommand(const RemoveContentInBracesData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			std::string handle = content[_data.get_index()];
			std::stringstream result;

			bool inner_mode = false;

			for (auto symbol : handle) {
				if (inner_mode) {
					if (symbol == '}')
						inner_mode = false;
				}
				else {
					if (symbol == '{')
						inner_mode = true;
					else 
						result << symbol;
				}
			}
			std::getline(result, content[_data.get_index()]);
		}
	};
}
