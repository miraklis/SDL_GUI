#include "UIInputBox.h"

namespace SDL_GUI {

	SDL_Color defaultBGColor{ 0,0,0,255 };
	SDL_Color defaultFGColor{ 255,255,255,255 };

	UIInputBox::UIInputBox(SDL_Renderer* renderer, std::string name)
		:UILabel(renderer, name, "") 
	{
		_focus = false;
		_maxChar = 10;
	}

	UIInputBox::UIInputBox(SDL_Renderer* renderer, std::string name, std::string caption,
						   int x, int y, size_t w, size_t h, bool autosize,
						   std::string fontName, size_t fontSize,
						   SDL_Color& bgColor, SDL_Color& fgColor,
						   HorizontalAlign hAlign, VerticalAlign vAlign)
		:UILabel(renderer, name, caption, 0, 0, 0, 0, true,
				  sFonts::TTF_TIMES, 16, defaultBGColor, defaultFGColor,
				  HorizontalAlign::Left, VerticalAlign::Top)
	{}

	UIInputBox::~UIInputBox() {
		SDL_StopTextInput();
	}

	void UIInputBox::HandleInput() {
		if(!_focus)
			return;
		SDL_Event event;
		SDL_PollEvent(&event);
		int len;
		bool changed{ false };
		switch(event.type) {
			case SDL_TEXTINPUT:
				if(_caption.size() < _maxChar) {
					_caption += event.text.text;
					changed = true;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_BACKSPACE:
						len = _caption.size();
						if(len > 0) {
							_caption = _caption.substr(0, len - 1);
							changed = true;
						}
						break;
					case SDLK_RETURN:
						OnInputFinished(true, _caption);
						break;
					case SDLK_ESCAPE:
						OnInputFinished(false, _caption);
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
		_focus = focus;
		if(focus)
			SDL_StartTextInput();
		else
			SDL_StopTextInput();
	}

	void UIInputBox::SetMaxChar(size_t maxChar) {
		_maxChar = maxChar;
	}

}