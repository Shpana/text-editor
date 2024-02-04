#include "text_space_view.h"

#include "imgui.h"
#include <string>
#include <algorithm>
#include <iostream>

namespace text_editor {

	void TextSpaceView::apply_command_to_content(const Command& command) {
		_space->apply_command_to_content(command);
		_update_selection_context();
	}

	void TextSpaceView::on_process() {
		if (ImGui::Begin("Text Space")) {
			int space_size = _space->get_content().size();

			for (int i = 0; i < space_size; ++i) {
				std::string line = _space->get_content()[i];
				std::string line_view = _generate_line_view(i, space_size, line);

				if (ImGui::Selectable(line_view.c_str(), _selection_context[i])) {
					if (!ImGui::GetIO().KeyCtrl)
						std::fill(_selection_context.begin(), _selection_context.end(), false);
					_selection_context[i] = true ^ _selection_context[i];
				}
			}
		}
		ImGui::End();
	}

	const std::vector<int>& TextSpaceView::get_selected_lines() const {
		std::vector<int> selected_lines;
		
		for (int i = 0; i < _selection_context.size(); i++) {
			bool selected = _selection_context[i];

			if (selected) {
				selected_lines.push_back(i);
			}
		}
		return selected_lines;
	}

	void TextSpaceView::_update_selection_context() {
		int space_size = _space->get_content().size();
		
		_selection_context.clear();
		_selection_context.reserve(space_size);
		
		for (int i = 0; i < space_size; i++) {
			_selection_context.push_back(false);
		}
	}

	std::string TextSpaceView::_generate_line_view(int index, int size, const std::string& line) {
		int max_number_length = 
			std::to_string(size).length();
		int current_number_length =
			std::to_string(index + 1).length();
		
		return std::string(max_number_length - current_number_length, ' ') + std::to_string(index + 1) + ' ' + line;
	}
}
