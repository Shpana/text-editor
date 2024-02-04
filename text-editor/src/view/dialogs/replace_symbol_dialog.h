#pragma once

#include <array>
#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/replace_symbol.h"
#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor {

	class ReplaceSymbolDialog : public CommandDialog {

	private:
		int _number = 1;
		int _symbol_number = 1;
		std::array<char, 1> _content;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			bool submited = submit_command_dialog("Replace Symbol", opened, _on_submition);
		
			if (submited) {
				ReplaceSymbolData data = {
					_number - 1, _symbol_number - 1, _content[0]
				}; 
				ReplaceSymbolCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_number(int& number) {
			clamp_value(number, 1, _space_view->get_content_size());
		}

		void _clamp_symbol_number(int& symbol_number, int index) {
			clamp_value(symbol_number, 1, _space_view->get_line_size(index));
		}

		std::function<bool()> _on_submition = [&]() -> bool {
			ImGui::InputInt("Number", &_number);
			_clamp_number(_number);

			ImGui::InputInt("Symbol Number", &_symbol_number);
			_clamp_symbol_number(_symbol_number, _number - 1);

			ImGui::InputText("Symbol", _content.data(), 2);
			return true;
		};
	};
}
