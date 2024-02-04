#pragma once

#include <string>
#include <memory>
#include <functional>

#include "text_space_view.h"
#include "dialogs/command_dialog.h"

namespace text_editor {

	class CommandsMenu {
		
	private:
		TextSpaceView* _space_view;

		bool _dialog_opened = true;
		std::unique_ptr<CommandDialog> _selected_dialog = nullptr;
	public:
		void on_process();

		CommandsMenu(TextSpaceView* space_view)
			: _space_view(space_view) {}
	private:
		void _view_insert_commands_tab();
		void _view_modification_commands_tab();
		void _view_algorithmic_commands_tab();
	
		void _handle_command(
			const char* title, 
			const char* description, 
			std::function<CommandDialog*()> on_selection
		);
	};
}
