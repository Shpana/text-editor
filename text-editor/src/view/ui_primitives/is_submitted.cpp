#include "is_submitted.h"

namespace text_editor {

	bool text_editor::is_submitted(const std::string& title, bool* is_opened) {
		static float button_heigth = 20.0f;

		bool submitted = false;

		ImGui::PushID(title.c_str());
		{
			ImGui::Separator();
			ImGui::Columns(2);
			submitted =
				ImGui::Button("Submit", ImVec2(-FLT_MIN, button_heigth));

			ImGui::NextColumn();
			if (ImGui::Button("Cancel", ImVec2(-FLT_MIN, button_heigth))) {
				*is_opened = false;
			}
			ImGui::Columns(1);
		}
		ImGui::PopID();

		return submitted;
	}
}
