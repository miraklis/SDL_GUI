#include "UIInputBox.h"

namespace SDL_GUI {

	UIInputBox::UIInputBox(SDL_Renderer* renderer, std::string name, SDL_Rect rect):
			UILabel(renderer, name, "", sFonts::TTF_TIMES, 24, rect.x, rect.y, rect.w, rect.h, false) {
		focus = false;
		maxChar = 10;
	}

	UIInputBox::~UIInputBox() {
		SDL_StopTextInput();
	}

	void UIInputBox::HandleInput() {
		if(!focus)
			return;
		SDL_Event event;
		SDL_PollEvent(&event);
		int len;
		bool changed{ false };
		switch(event.type) {
			case SDL_TEXTINPUT:
				if(caption.size() < maxChar) {
					caption += event.text.text;
					changed = true;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_BACKSPACE:
						len = caption.size();
						if(len > 0) {
							caption = caption.substr(0, len - 1);
							changed = true;
						}
						break;
					case SDLK_RETURN:
						OnInputFinished(true, caption);
						break;
					case SDLK_ESCAPE:
						OnInputFinished(false, caption);
						break;
				}
				break;
			default:
				break;
		}
		if(changed) {
			updateText();
			Align();
		}
	}

	void UIInputBox::SetFocus(bool focus) {
		this->focus = focus;
		if(focus)
			SDL_StartTextInput();
		else
			SDL_StopTextInput();
	}

	void UIInputBox::SetMaxChar(size_t maxChar) {
		this->maxChar = maxChar;
	}

}