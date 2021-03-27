#include "UILabel.h"

namespace SDL_GUI {
	
	static SDL_Color defaultBGColor{ 0,0,0,255 };
	static SDL_Color defaultFGColor{ 255,255,255,255 };

	UILabel::UILabel(SDL_Renderer* renderer, std::string name, std::string caption)
		:UILabel(renderer, name, caption, 0, 0, 0, 0, true, 
				 sFonts::TTF_TIMES, 16, defaultBGColor, defaultFGColor,
				 HorizontalAlign::Left, VerticalAlign::Top)
	{}

	UILabel::UILabel(SDL_Renderer* renderer, std::string name, std::string caption, 
					 int x, int y, size_t w, size_t h, bool autosize, 
					 std::string fontName, size_t fontSize,
					 SDL_Color& bgColor, SDL_Color& fgColor,
					 HorizontalAlign hAlign, VerticalAlign vAlign)
			:UITextComponent(name, caption, x, y, w, h, fontName, fontSize, bgColor, fgColor)
	{
		_renderer = renderer;
		_autosize = autosize;
		_hAlign = hAlign;
		_vAlign = vAlign;
		_txtOffsetX = _txtOffsetY = 0;
		updateText();
	}

	UILabel::~UILabel() 
	{}

	void UILabel::SetSize(size_t w, size_t h) {
		if(_autosize)
			return;
		UITextComponent::SetSize(w, h);
		updateText();
		Align();
		OnResized(this);
	}

	void UILabel::SetText(std::string caption) {
		UITextComponent::SetText(caption);
		updateText();
		Align();
		OnTextChanged(this);
	}

	void UILabel::SetFont(std::string fontName, size_t fontSize) {
		UITextComponent::SetFont(fontName, fontSize);
		updateText();
		Align();
	}

	void UILabel::AlignHorizontal(HorizontalAlign hAlign) {
		_hAlign = hAlign;
		switch(hAlign) {
			case HorizontalAlign::Left:
				_txtOffsetX = 0;
				break;
			case HorizontalAlign::Center:
				_txtOffsetX = (_rect.w / 2) - (_textRegion.w / 2);
				break;
			case HorizontalAlign::Right:
				_txtOffsetX = _rect.w - _textRegion.w;
				break;
		}
	}

	void UILabel::AlignVertical(VerticalAlign vAlign) {
		_vAlign = vAlign;
		switch(vAlign) {
			case VerticalAlign::Top:
				_txtOffsetY = 0;
				break;
			case VerticalAlign::Middle:
				_txtOffsetY = (_rect.h / 2) - (_textRegion.h / 2);
				break;
			case VerticalAlign::Bottom:
				_txtOffsetY = _rect.h - _textRegion.h;
				break;
		}
	}

	void UILabel::Align() {
		AlignHorizontal(_hAlign);
		AlignVertical(_vAlign);
	}

	void UILabel::SetAutosize(bool autosize) {
		_autosize = autosize;
		updateText();
	}

	void UILabel::Render() {
		if(!_visible)
			return;
		SDL_SetRenderDrawColor(_renderer, _bgColor.r, _bgColor.g, _bgColor.b, _bgColor.a);
		SDL_RenderFillRect(_renderer, &_rect);
		SDL_SetRenderDrawColor(_renderer, _fgColor.r, _fgColor.g, _fgColor.b, _fgColor.a);
		SDL_Rect src;
		SDL_Rect dest;
		src.x = std::abs(std::min(0, _txtOffsetX));
		dest.x = _rect.x + std::max(0, _txtOffsetX);
		src.y = std::abs(std::min(0, _txtOffsetY));
		dest.y = _rect.y + std::max(0, _txtOffsetY);
		src.w = dest.w = std::min(_rect.w, _textRegion.w);
		src.h = dest.h = std::min(_rect.h, _textRegion.h);
		SDL_RenderCopy(_renderer, _texture, &src, &dest);
	}

	void UILabel::updateText() {
		UITextComponent::updateText();
		if(_autosize || _rect.w == 0) {
			_rect.w = _textRegion.w;
		}
		if(_autosize || _rect.h == 0) {
			_rect.h = _textRegion.h;
		}
	}

}
