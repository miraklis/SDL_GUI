#ifndef UITEXTCOMPONENT_H
#define UITEXTCOMPONENT_H

#include "UIComponent.h"

namespace SDL_GUI {

    class UITextComponent : public UIComponent {
	public:
		virtual ~UITextComponent();
		virtual void SetText(std::string caption);
		virtual void SetColor(const SDL_Color& bgColor, const SDL_Color& fgColor);
		virtual void SetFont(std::string fntName, size_t fntSize);
		size_t GetTextWidth() const;
		Event<UITextComponent*> OnTextChanged;
		virtual void HandleInput() {}
		virtual void SetFocus(bool focus) {}
		virtual void SetMaxChar(size_t maxChar)	{}
	protected:
		UITextComponent(std::string name, std::string caption);
		UITextComponent(std::string name, std::string caption, int x, int y, size_t w, size_t h,
						std::string fontName, size_t fontSize, SDL_Color& bgColor, SDL_Color& fgColor);
		std::string _caption;
		SDL_Color _fgColor;
		SDL_Color _bgColor;
		SDL_Rect _textRegion;
		TTF_Font* _font;
		SDL_Texture* _texture;
		virtual void updateText();
    };

}

#endif // UITEXTCOMPONENT_H