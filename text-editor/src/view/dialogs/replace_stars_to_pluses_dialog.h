#pragma once

#include <array>
#include <functional>

#include "command_dialog.h"
#include "utils/clamp_value.h"
#include "domain/commands/replace_stars_to_pluses.h"
#include "view/text_space_view.h"
#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor {

	class ReplaceStarsToPlusesDialog : public CommandDialog {

	private:
		int _start = 1;
		int _end = -1;
	public:
		using CommandDialog::CommandDialog;

		virtual void on_process(bool* opened) {
			if (_end == -1) {
				_end = _space_view->get_content_size();
			}

			bool submited = submit_command_dialog("Replace Stars To Pluses", opened, _on_submition);

			if (submited) {
				ReplaceStarsToPlusesData data = {
					_start, _end
				};
				ReplaceStarsToPlusesCommand command = { data };
				_space_view->apply_command_to_content(command);
			}
		}
	private:
		void _clamp_start(int& start, int end) {
			clamp_value(start, 1, end);
		}

		void _clamp_end(int& end, int start) {
			clamp_value(end, start, _space_view->get_content_size());
		}

		std::function<bool()> _on_submition = [&]() {
			ImGui::InputInt("Start", &_start);
			_clamp_start(_start, _end);

			ImGui::InputInt("End", &_end);
			_clamp_end(_end, _start);
			return true;
		};
	};
}
