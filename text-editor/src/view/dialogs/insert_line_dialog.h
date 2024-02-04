#pragma once

#include <iostream>
#include <array>
#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/insert_line.h"
#include "view/text_space_view.h"
#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor{

	class InsertLineDialog : public CommandDialog {
	
	private:
		int _index = 0;
		std::array<char, MAX_LINE_LENGTH> _content;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			bool submited = submit_command_dialog("Insert Line", opened, _on_submition);

			if (submited) {
				InstertLineData data = {
					_index, _content.data()
				};
				InsertLineCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_index(int& index) {
			clamp_value(index, 0, _space_view->get_content_size());
		}

		std::function<bool()> _on_submition = [&]() -> bool {
			ImGui::InputInt("Index", &_index);
			_clamp_index(_index);

			ImGui::InputText("Content", _content.data(), MAX_LINE_LENGTH);
			return true;
		};
	};
}
