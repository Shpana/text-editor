#pragma once

#include "domain/text_space.h"

namespace text_editor {

	class TextSpaceView {

	private:
		TextSpace* _space;
		std::vector<bool> _selection_context;
	public:
		int get_content_size() const {
			return _space->get_content().size();
		}

		int get_line_size(int index) const {
			return _space->get_content()[index].size();
		}

		void apply_command_to_content(const Command& command);

		void on_process();

		TextSpaceView(TextSpace* space)
			: _space(space) { _update_selection_context(); }

		const std::vector<int>& get_selected_lines() const;
	private:
		void _update_selection_context();
		std::string _generate_line_view(int index, int size, const std::string& line);
	};
}
