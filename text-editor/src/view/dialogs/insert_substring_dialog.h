#pragma once

#include <array>
#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/insert_substring.h"
#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor {
	
	class InsertSubstringDialog : public CommandDialog {

	private:
		int _number = 1;
		int _position = 0;
		std::array<char, MAX_LINE_LENGTH> _subline;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			bool submited = submit_command_dialog("Insert Substring", opened, _on_submition);

			if (submited) {
				InsertSubstringData data = {
					_number - 1, _position, _subline.data()
				};
				InsertSubstringCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_number(int& number) {
			clamp_value(number, 1, _space_view->get_content_size());
		}

		void _clamp_position(int& position, int index) {
			clamp_value(position, 0, _space_view->get_line_size(index));
		}

		std::function<bool()> _on_submition = [&]() -> bool {
			ImGui::InputInt("Number", &_number);
			_clamp_number(_number);

			ImGui::InputInt("Position", &_position);
			_clamp_position(_position, _number - 1);

			ImGui::InputText("Subline", _subline.data(), MAX_LINE_LENGTH);
			return true;
		};
	};
}
