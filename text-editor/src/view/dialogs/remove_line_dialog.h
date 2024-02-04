#pragma once

#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/remove_line.h"
#include "view/text_space_view.h"
#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor {

	class RemoveLineDialog : public CommandDialog {
	
	private:
		int _number = 1;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			bool submited = submit_command_dialog("Remove Line", opened, _on_submition);
		
			if (submited) {
				RemoveLineData data = { _number - 1 };
				RemoveLineCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_number(int& number) {
			clamp_value(number, 1, _space_view->get_content_size());
		}

		std::function<bool()> _on_submition = [&]() -> bool {
			ImGui::InputInt("Number", &_number);
			_clamp_number(_number);
			return true;
		};
	};
}
