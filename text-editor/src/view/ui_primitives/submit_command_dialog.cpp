#include "submit_command_dialog.h"

namespace text_editor {

	bool submit_command_dialog(const std::string& title, bool* must_show, std::function<bool()> content) {
		bool submited = false;

		if (*must_show) {
			if (ImGui::Begin(title.c_str(), NULL, COMMAND_DIALOG_FLAGS)) {
				content();
				submited = is_submitted(title, must_show);

				if (submited) {
					*must_show = false;
				}
			}
			ImGui::End();
		}
		return submited;
	}
}
