#pragma once

#include "imgui.h"

#include <string>
#include <functional>

#include "is_submitted.h"

namespace text_editor {

	static ImGuiWindowFlags COMMAND_DIALOG_FLAGS = 
		ImGuiWindowFlags_NoDocking;

	bool submit_command_dialog(const std::string& title, bool* must_show, std::function<bool()> content);
}
