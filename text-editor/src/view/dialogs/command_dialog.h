#pragma once

#include "../text_space_view.h"

namespace text_editor {

	class CommandDialog {
	
	protected:
		TextSpaceView* _space_view;
	public:
		virtual void on_process(bool* opened) = 0;

		CommandDialog(TextSpaceView* space_view)
			: _space_view(space_view) {}
	};
}
