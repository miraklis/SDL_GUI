#ifndef UITEXTCOMPONENT_H
#define UITEXTCOMPONENT_H

#include "UIComponent.h"

namespace SDL_GUI {

    class UITextComponent : public UIComponent {
	public:
		UITextComponent(SDL_Renderer* renderer, std::string name, std::string caption);
		UITextComponent(SDL_Renderer* renderer, std::string name, std::string caption, int x, int y, size_t w, size_t h,
						std::string fontName, size_t fontSize, SDL_Color& fgColor);
		virtual ~UITextComponent();
		virtual void Render() override;
		virtual void SetText(std::string caption);
		virtual void SetColor(const SDL_Color& fgColor);
		virtual void SetFont(std::string fntName, size_t fntSize);
		virtual std::string GetText() const;
		size_t GetTextWidth() const;
	protected:
		std::string _caption;
		SDL_Color _fgColor;
		SDL_Rect _textRegion;
		TTF_Font* _font;
		SDL_Texture* _texture;
	private:
		void updateText();
    };

}

#endif // UITEXTCOMPONENT_H