#pragma once

#include <string>
#include <vector>
#include <sstream>

#include "command.h"

namespace text_editor {
	
	class ReplaceStarsToPlusesData : public CommandExecutionData {

	private:
		int _start;
		int _end;
	public:
		int get_start() const { return _start; }
		int get_end() const { return _end; }

		ReplaceStarsToPlusesData(int start, int end)
			: _start(start), _end(end) {}
	};

	class ReplaceStarsToPlusesCommand : public Command {

	private:
		const ReplaceStarsToPlusesData& _data;
	public:
		ReplaceStarsToPlusesCommand(const ReplaceStarsToPlusesData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			for (int i = _data.get_start() - 1; i < _data.get_end(); i++) {
				std::string handle = content[i];
				std::stringstream result;

				int stars_count = 0;
				for (auto symbol : handle) {
					if (symbol == '*')
						stars_count += 1;
					else {
						if (stars_count == 1) {
							result << '*';
						}
						else if (stars_count >= 1) {
							for (int j = 0; j < stars_count / 2; j++) {
								result << '+';
							}
						}
						stars_count = 0;
						result << symbol;
					}
				}
				if (stars_count == 1) {
					result << '*';
				}
				else if (stars_count >= 1) {
					for (int j = 0; j < stars_count / 2; j++) {
						result << '+';
					}
				}
				std::getline(result, content[i]);
			}
		}
	};
}
