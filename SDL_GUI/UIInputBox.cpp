#include "UIInputBox.h"

namespace SDL_GUI {

	static SDL_Color defaultBGColor{ 0,0,0,255 };
	static SDL_Color defaultFGColor{ 255,255,255,255 };

	UIInputBox::UIInputBox(SDL_Renderer* renderer, std::string name, std::string title)
		:UIInputBox(renderer, name, title, 0, 0, 10, sFonts::TTF_TIMES, 16, defaultBGColor, defaultFGColor, HorizontalAlign::Left)
	{}

	UIInputBox::UIInputBox(SDL_Renderer* renderer, std::string name, std::string title,
						   int x, int y, size_t maxChar, std::string fontName, size_t fontSize,
						   SDL_Color& bgColor, SDL_Color& fgColor, HorizontalAlign hTextAlign)
		:UIPanel(renderer, name, x, y)
	{
		_autosize = false;
		_focus = false;
		_maxChar = maxChar;
		_rect.w = (maxChar * fontSize) + fontSize;
		_rect.h = 2 * fontSize;
		std::unique_ptr<UILabel> item;
		if(!title.empty()) {
			item = std::make_unique<UILabel>(renderer, "title", title, x, y, _rect.w, fontSize, false,
											fontName, fontSize, bgColor, fgColor,
											HorizontalAlign::Left, VerticalAlign::Middle);
			_components.push_back(std::move(item));
		}
		item = std::make_unique<UILabel>(renderer, "content", "", x, y + fontSize, _rect.w, fontSize, false,
										   fontName, fontSize, bgColor, fgColor,
										   hTextAlign, VerticalAlign::Middle);
		_components.push_back(std::move(item));
	}

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
		size_t contentIndex = _components.size() - 1;
		std::string txt = _components[contentIndex]->GetText();
		switch(event.type) {
			case SDL_TEXTINPUT:
				if(txt.size() < _maxChar) {
					txt += event.text.text;
					changed = true;
				}
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_BACKSPACE:
						len = txt.size();
						if(len > 0) {
							txt = txt.substr(0, len - 1);
							changed = true;
						}
						break;
					case SDLK_RETURN:
						OnInputFinished(true, txt);
						break;
					case SDLK_ESCAPE:
						OnInputFinished(false, txt);
						break;
				}
				break;
			default:
				break;
		}
		if(changed) {
			_components[contentIndex]->SetText(txt);
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