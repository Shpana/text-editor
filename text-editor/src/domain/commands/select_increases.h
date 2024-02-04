#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "command.h"
#include "utils/is_digit.h"
#include "utils/is_increasing_digit_subsequence.h"

namespace text_editor {

	class SelectIncreasesData : public CommandExecutionData {
	
	private:
		int _number;
	public:
		int get_number() const { return _number; }

		SelectIncreasesData(int number)
			: _number(number) {}
	};

	class SelectIncreasesCommand : public Command {
	
	private:
		const SelectIncreasesData& _data;
	public:
		SelectIncreasesCommand(const SelectIncreasesData& data) 
			: _data(data) {}

		virtual void apply_to(std::vector<std::string>& content) const {
			std::string handle = content[_data.get_number()];
			std::stringstream result;
			std::stringstream digit_subsequence; 

			for (auto symbol : handle) {
				if (is_digit(symbol)) {
					digit_subsequence << symbol;
				}
				else {
					std::string buffer;
					digit_subsequence >> buffer;

					if (buffer.size() > 1) {
						if (is_increasing_digit_subsequence(buffer)) {
							result << buffer;
						}
					}
					digit_subsequence.clear();
					result << symbol;
				}
			}
			std::string buffer;
			digit_subsequence >> buffer;

			if (buffer.size() > 0) {
				if (is_increasing_digit_subsequence(buffer)) {
					result << buffer;
				}
			}
			digit_subsequence.clear();
			std::getline(result, content[_data.get_number()]);
		}
	};
}
