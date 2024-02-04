#include "commands_menu.h"

#include "imgui.h"

#include "ui_primitives/help_marker.h"

#include "dialogs/insert_substring_dialog.h"
#include "dialogs/insert_line_dialog.h"
#include "dialogs/repeat_line_dialog.h"
#include "dialogs/insert_many_lines_dialog.h"
#include "dialogs/remove_line_dialog.h"
#include "dialogs/replace_symbol_dialog.h"
#include "dialogs/find_and_replace_dialog.h"
#include "dialogs/remove_leading_zeros_dialog.h"
#include "dialogs/select_increses_dialog.h"
#include "dialogs/remove_content_in_braces_dialog.h"
#include "dialogs/replace_stars_to_pluses_dialog.h"

namespace text_editor {

	void CommandsMenu::on_process() {
		if (ImGui::Begin("Commands Menu")) {
			if (ImGui::BeginTabBar("Commands Menu Tab Bar")) {
				_view_insert_commands_tab();
				_view_modification_commands_tab();
				_view_algorithmic_commands_tab();
				ImGui::EndTabBar();
				
				if (_selected_dialog != nullptr) {
					_selected_dialog->on_process(&_dialog_opened);
				}
			}
		}
		ImGui::End();
	}

	void CommandsMenu::_handle_command(
		const char* title,
		const char* description, 
		std::function<CommandDialog*()> on_selection
	) {
		if (ImGui::Button(title)) {
			_dialog_opened = true;
			_selected_dialog = std::unique_ptr<CommandDialog>(on_selection());
		}
		ImGui::SameLine();
		help_marker(description);
	}

	void CommandsMenu::_view_insert_commands_tab() {
		if (ImGui::BeginTabItem("Insertion")) {
			_handle_command(
				"Insert line", 
				"Insertion of one line after n-th (line and n are entered). If you enter n = 0, then insert at the beginning.",
				[&]() {
					return new InsertLineDialog(_space_view);
				});
			_handle_command(
				"Repeat line",
				"Insert one line many times.",
				[&]() {
					return new RepeatLineDialog(_space_view);
				});
			_handle_command(
				"Insert many lines",
				"Inserting multiple lines, starting with the n-th.",
				[&]() {
					return new InsertManyLinesDialog(_space_view);
				});
			_handle_command(
				"Remove line",
				"Delete line by number n (lines are numbered from one).", 
				[&]() {
					return new RemoveLineDialog(_space_view);
				});

			ImGui::EndTabItem();
		}
	}

	void CommandsMenu::_view_modification_commands_tab() {
		if (ImGui::BeginTabItem("Modification")) {
			_handle_command(
				"Insert substring",
				"Insert a substring into the n-th string, starting at the m-th position.",
				[&]() {
					return new InsertSubstringDialog(_space_view);
				});
			_handle_command(
				"Replace symbol", 
				"Replace m-th character in n-th string.", 
				[&]() {
					return new ReplaceSymbolDialog(_space_view);
				});
			_handle_command(
				"Find and replace substring",
				"Contextual replacement of a substring with a substring for a given range of lines of text (default in all text).",
				[&]() {
					return new FindAndReplaceDialog(_space_view);
				});

			ImGui::EndTabItem();
		}
	}

	void CommandsMenu::_view_algorithmic_commands_tab() {
		if (ImGui::BeginTabItem("Algorithmic")) {
			_handle_command(
				"Remove leading zeros",
				"In the given range of strings, remove leading zeros from each group of consecutive digits."
				"If the group of digits consists only of zeros, then replace it with one zero. The rest of the characters do not change.",
				[&]() {
					return new RemoveLeadingZerosDialog(_space_view);
				});
			_handle_command(
				"Select Increases",
				"Leave only those groups of consecutive digits in the line (in a group of at least two digits)" 
				"that are composed of digits with increasing values." 
				"Delete all other digits and groups of digits. The rest of the characters do not change.",
				[&]() {
					return new SelectIncreasesDialog(_space_view);
				});
			_handle_command(
				"Replace Stars To Pluses",
				"Replace each group of N adjacent characters * with a group of N/2 adjacent characters +. Single asterisks do not change.",
				[&]() {
					return new ReplaceStarsToPlusesDialog(_space_view);
				});
			_handle_command(
				"Remove Content In Braces",
				"fff",
				[&]() {
					return new RemoveContentInBracesDialog(_space_view);
				});

			ImGui::EndTabItem();
		}
	}
}
