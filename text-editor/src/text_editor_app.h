#pragma once

#include <functional>

#include "imgui.h"
#include "imgui-SFML.h"
#include <SFML/Graphics.hpp>

#include "view/commands_menu.h"
#include "view/text_space_view.h"

namespace text_editor {

	class TextEditorApp {
	
	private:
		sf::RenderWindow* _window;
		int _frame_rate_limit = 60;

		text_editor::CommandsMenu* _commands_menu;

		text_editor::TextSpace _space = {
			{
				"Lorem Ipsum is simply dummy text of the "
				"printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text "
				"ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. "
				"It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It "
				"was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing "
				"software like Aldus PageMaker including versions of Lorem Ipsum."
			}
		};
		text_editor::TextSpaceView* _space_view;
	private:
		void _handle_dockspace(std::function<void()> hook);

		void _handle_events();
		void _on_process(sf::Clock& clock);
	public:
		void run();

		TextEditorApp(
			const std::string& title, const sf::Vector2u& resolution);
	};
}
