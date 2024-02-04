#pragma once

#include <string>
#include <vector>

#include "command.h"

namespace text_editor {

	class RemoveLineData : public CommandExecutionData {

	private:
		int _index;
	public:
		int get_index() const { return _index; }

		RemoveLineData(int index)
			: _index(index) {}
	};

	class RemoveLineCommand : public Command {

	private:
		const RemoveLineData& _data;
	public:
		RemoveLineCommand(const RemoveLineData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			content.erase(content.begin() + _data.get_index());
		}
	};
}
