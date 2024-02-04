#pragma once

#include <vector>
#include <array>
#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/insert_many_lines.h"
#include "view/text_space_view.h"
#include "view/ui_primitives/submit_command_dialog.h"

static const int MAX_LINES_COUNT = 16;

namespace text_editor {

	class InsertManyLinesDialog : public CommandDialog {

	private:
	private:
		int _index = 0;
		int _lines_count = 1;
		std::array<std::array<char, MAX_LINE_LENGTH>, MAX_LINES_COUNT> _contents;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			bool submited = submit_command_dialog("Insert Many Lines", opened, _on_submition);

			if (submited) {
				std::vector<std::string> lines;

				for (int i = 0; i < _lines_count; i++) {
					lines.push_back(std::string(_contents[i].data()));
				}

				InsertManyLinesData data = {
					_index, lines
				};
				InsertManyLinesCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_index(int& index) {
			clamp_value(index, 0, _space_view->get_content_size());
		}

		void _clamp_lines_count(int& lines_count) {
			clamp_value(lines_count, 1, MAX_LINES_COUNT);
		}

		std::function<bool()> _on_submition = [&]() -> bool {
			ImGui::InputInt("Index", &_index);
			_clamp_index(_index);

			ImGui::InputInt("Lines Count", &_lines_count);
			_clamp_lines_count(_lines_count);

			ImGui::Separator();
			ImGui::Text("Content to insert");

			for (int i = 0; i < _lines_count; i++) {
				ImGui::InputText(
					("##" + std::to_string(i)).c_str(), _contents[i].data(), MAX_LINE_LENGTH);
			}
			return true;
		};
	};
}
