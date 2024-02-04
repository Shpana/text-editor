#include <iostream>

#include "text_editor_app.h"

int main() {
	text_editor::TextEditorApp* app 
		= new text_editor::TextEditorApp {
			"Text Editor", { 800, 600 }
	};
	app->run();
}
