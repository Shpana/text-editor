#include "text_editor_app.h"

#include "view/ui_primitives/submit_command_dialog.h"

namespace text_editor {

	void TextEditorApp::_on_process(sf::Clock& clock) {
		ImGui::SFML::Update(*_window, clock.restart());
		{
			_handle_dockspace([&]() {
				_commands_menu->on_process();
				_space_view->on_process();
				});
		}
		_window->clear();
		ImGui::SFML::Render(*_window);
		_window->display();
	}

	void TextEditorApp::_handle_events() {
		static sf::Event event;

		while (_window->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				_window->close();
			}
		}
	}

	void TextEditorApp::run() {
		_window->setFramerateLimit(_frame_rate_limit);

		ImGui::SFML::Init(*_window);
		{
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			
			sf::Clock clock;
			while (_window->isOpen()) {
				_handle_events();
				_on_process(clock);
			}
		}
		ImGui::SFML::Shutdown();
	}

	TextEditorApp::TextEditorApp(
			const std::string& title, const sf::Vector2u& resolution) {
		_space_view = new TextSpaceView(&_space);
		_commands_menu = new CommandsMenu(_space_view);
		
		_window = new sf::RenderWindow(sf::VideoMode(resolution.x, resolution.y), title);
	}

    void TextEditorApp::_handle_dockspace(std::function<void()> hook) {
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        bool p_open = true;
        ImGui::Begin("DockSpace", &p_open, window_flags);
        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("DockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        hook();
        ImGui::End();
    }
}
