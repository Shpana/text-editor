#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "command.h"
#include "utils/is_digit.h"

namespace text_editor {

	class RemoveLeadingZerosData : public CommandExecutionData {
	
	private:
		int _start;
		int _end;
	public:
		int get_start() const { return _start; }
		int get_end() const { return _end; }
		
		RemoveLeadingZerosData(int start, int end)
			: _start(start), _end(end) {}
	};

	class RemoveLeadingZerosCommand : public Command {

	private:
		const RemoveLeadingZerosData& _data;
	public:
		RemoveLeadingZerosCommand(const RemoveLeadingZerosData& data)
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			for (int i = _data.get_start() - 1; i < _data.get_end(); i++) {
				std::stringstream result;
				std::string handle = content[i];
				
				bool only_digits = true;
				bool ignore_zeros = true;
				bool previous_is_digit = false;

				for (auto symbol : handle) {
					if (is_digit(symbol)) {
						if (symbol == '0' && ignore_zeros) {
							only_digits = true;
						}
						else {
							result << symbol;
							ignore_zeros = false;
						}
						previous_is_digit = true;
					}
					else {
						if (ignore_zeros && previous_is_digit) {
							result << '0';
						}
						only_digits = false;
						result << symbol;
						ignore_zeros = true;
						previous_is_digit = false;
					}
				}
				if (only_digits && ignore_zeros) {
					result << '0';
				}
				std::getline(result, content[i]);
			}
		}
	};
}
