#ifndef UILABEL_H
#define UILABEL_H

#include "UIMain.h"
#include "UITextComponent.h"

namespace SDL_GUI {

	class UILabel : public UITextComponent {
	public:
		UILabel(SDL_Renderer* renderer, std::string name, std::string caption);
		UILabel(SDL_Renderer* renderer, std::string name, std::string caption, 
				int x, int y, size_t w, size_t h, bool autosize,
				std::string fontName, size_t fontSize,
				SDL_Color& bgColor, SDL_Color& fgColor,
				HorizontalAlign hAlign, VerticalAlign vAlign);
		virtual ~UILabel() override;
		void Render() override;
		void SetSize(size_t w, size_t h) override;
		void SetText(std::string caption) override;
		void SetFont(std::string fontName, size_t fontSize) override;
		void AlignHorizontal(HorizontalAlign hAligh);
		void AlignVertical(VerticalAlign vAlign);
		void Align();
		void SetAutosize(bool autosize);
	protected:
		bool _autosize;
		int _txtOffsetX;
		int _txtOffsetY;
		HorizontalAlign _hAlign;
		VerticalAlign _vAlign;
		void updateText() override;
	};

}

#endif //UILABEL_H