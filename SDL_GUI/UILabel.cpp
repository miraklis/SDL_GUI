#include "UILabel.h"

namespace SDL_GUI {

	UILabel::UILabel(SDL_Renderer* renderer, std::string name, std::string caption, std::string fontName, size_t fontSize,
					 int posX, int posY, size_t w, size_t h, bool autosize, HorizontalAlign hAlign, VerticalAlign vAlign,
					 SDL_Color bgColor, SDL_Color fgColor) :
			UIComponent(renderer, name, posX, posY, w, h, false) {
		this->autosize = autosize;
		this->bgColor = bgColor;
		this->fgColor = fgColor;
		this->hAlign = hAlign;
		this->vAlign = vAlign;
		this->caption = caption;
		this->font = TTF_OpenFont(fontName.c_str(), fontSize);
		txtOffsetX = txtOffsetY = 0;
		texture = nullptr;
		textRegion.x = 0;
		textRegion.y = 0;
		updateText();
	}

	UILabel::~UILabel() {
		if(font)
			TTF_CloseFont(font);
		if(texture)
			SDL_DestroyTexture(texture);
	}

	void UILabel::SetSize(size_t w, size_t h) {
		if(autosize)
			return;
		UIComponent::SetSize(w, h);
		Align();
	}

	void UILabel::SetText(std::string caption) {
		if(this->caption == caption)
			return;
		this->caption = caption;
		updateText();
		Align();
		OnTextChanged(this);
	}

	void UILabel::SetColor(const SDL_Color& bgColor, const SDL_Color& fgColor) {
		this->bgColor = bgColor;
		this->fgColor = fgColor;
		updateText();
	}

	void UILabel::SetFont(std::string fntName, size_t fntSize) {
		font = TTF_OpenFont(fntName.c_str(), fntSize);
		updateText();
		Align();
	}

	void UILabel::AlignHorizontal(HorizontalAlign hAlign) {
		this->hAlign = hAlign;
		switch(hAlign) {
			case HorizontalAlign::Left:
				txtOffsetX = 0;
				break;
			case HorizontalAlign::Center:
				txtOffsetX = (rect.w / 2) - (textRegion.w / 2);
				break;
			case HorizontalAlign::Right:
				txtOffsetX = rect.w - textRegion.w;
				break;
		}
	}

	void UILabel::AlignVertical(VerticalAlign vAlign) {
		this->vAlign = vAlign;
		switch(vAlign) {
			case VerticalAlign::Top:
				txtOffsetY = 0;
				break;
			case VerticalAlign::Middle:
				txtOffsetY = (rect.h / 2) - (textRegion.h / 2);
				break;
			case VerticalAlign::Bottom:
				txtOffsetY = rect.h - textRegion.h;
				break;
		}
	}

	void UILabel::Align() {
		AlignHorizontal(hAlign);
		AlignVertical(vAlign);
	}

	void UILabel::SetAutosize(bool autosize) {
		this->autosize = autosize;
	}

	int UILabel::GetTextWidth() const {
		return textRegion.w;
	}

	void UILabel::Render() {
		if(!visible)
			return;
		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, fgColor.r, fgColor.g, fgColor.b, fgColor.a);
		SDL_Rect src;
		SDL_Rect dest;
		src.x = std::abs(std::min(0, txtOffsetX));
		dest.x = rect.x + std::max(0, txtOffsetX);
		src.y = std::abs(std::min(0, txtOffsetY));
		dest.y = rect.y + std::max(0, txtOffsetY);
		src.w = dest.w = std::min(rect.w, textRegion.w);
		src.h = dest.h = std::min(rect.h, textRegion.h);
		SDL_RenderCopy(renderer, texture, &src, &dest);
	}

	void UILabel::updateText() {
		if(font == nullptr)
			return;
		if(!caption.empty()) {
			SDL_Surface* surface = TTF_RenderText_Blended(font, caption.c_str(), fgColor);
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			SDL_QueryTexture(texture, nullptr, nullptr, &textRegion.w, &textRegion.h);
		} else {
			textRegion.w = 0;
			textRegion.h = 0;
		}
		if(autosize || rect.w == 0) {
			rect.w = textRegion.w;
		}
		if(autosize || rect.h == 0) {
			rect.h = textRegion.h;
		}
	}

}
