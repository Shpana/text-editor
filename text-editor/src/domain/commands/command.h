#pragma once

namespace text_editor {

	class CommandExecutionData {
	};

	class Command {

	public:
		virtual void apply_to(std::vector<std::string>& content) const = 0;
	};
}
