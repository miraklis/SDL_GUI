#include "UITextComponent.h"

namespace SDL_GUI {

	static SDL_Color defaultFGColor{ 255,255,255,255 };

	UITextComponent::UITextComponent(SDL_Renderer* renderer, std::string name, std::string caption)
		:UITextComponent(renderer, name, caption, 0, 0, 0, 0,
						 sFonts::TTF_TIMES, 16, defaultFGColor)
	{}

	UITextComponent::UITextComponent(SDL_Renderer* renderer, std::string name, std::string caption, int x, int y, size_t w, size_t h,
									 std::string fontName, size_t fontSize, SDL_Color& fgColor)
		:UIComponent(renderer, name, x, y, w, h)
	{
		_caption = caption;
		_font = TTF_OpenFont(fontName.c_str(), fontSize);
		_fgColor = fgColor;
		_texture = nullptr;
		_textRegion = { 0,0,0,0 };
		updateText();
	}

	UITextComponent::~UITextComponent()
	{
		if(_font)
			TTF_CloseFont(_font);
		if(_texture)
			SDL_DestroyTexture(_texture);
	}

	void UITextComponent::Render()
	{
		if(!_visible)
			return;
		SDL_SetRenderDrawColor(_renderer, _fgColor.r, _fgColor.g, _fgColor.b, _fgColor.a);
		_rect.w = _textRegion.w;
		_rect.h = _textRegion.h;
		SDL_RenderCopy(_renderer, _texture, nullptr, &_rect);
	}

	void UITextComponent::SetText(std::string caption)
	{
		if(_caption == caption)
			return;
		_caption = caption;
		updateText();
	}

	void UITextComponent::SetColor(const SDL_Color& fgColor)
	{
		_fgColor = fgColor;
		updateText();
	}

	void UITextComponent::SetFont(std::string fntName, size_t fntSize)
	{
		_font = TTF_OpenFont(fntName.c_str(), fntSize);
	}

	std::string UITextComponent::GetText() const
	{
		return _caption;
	}

	size_t UITextComponent::GetTextWidth() const
	{
		return _textRegion.w;
	}

	void UITextComponent::updateText()
	{
		if(_font == nullptr)
			return;
		if(!_caption.empty()) {
			SDL_Surface* surface = TTF_RenderText_Blended(_font, _caption.c_str(), _fgColor);
			_texture = SDL_CreateTextureFromSurface(_renderer, surface);
			SDL_FreeSurface(surface);
			SDL_QueryTexture(_texture, nullptr, nullptr, &_textRegion.w, &_textRegion.h);
		} else {
			_textRegion.w = 0;
			_textRegion.h = 0;
		}
	}

}