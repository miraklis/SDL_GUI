#ifndef UIPANEL_H
#define UIPANEL_H

#include "UIMain.h"
#include "UIComponent.h"
#include "UILabel.h"

namespace SDL_GUI {

	class UIPanel : public UIComponent {
	public:
		UIPanel(SDL_Renderer* renderer, std::string name,
				int x, int y, size_t w, size_t h, bool autosize,
				std::string fontName, size_t fontSize,
				HorizontalAlign hAlign, VerticalAlign vAlign,
				SDL_Color bgColor, SDL_Color fgColor);
		~UIPanel();
		UILabel* operator [](size_t index);
		UILabel* operator [](std::string name);
		void Render() override;
		void SetPos(int x, int y) override;
		void SetSize(size_t w, size_t h) override;
		virtual void AddItem(std::string name, std::string caption);
		void RemoveItem(std::string name);
		void ClearItems();
		void AlignTextHorizontal(HorizontalAlign hAligh);
		void AlignTextVertical(VerticalAlign vAlign);
		void AlignHorizontal(HorizontalAlign hAlign);
		void AlignVertical(VerticalAlign vAlign);
		void SetFont(std::string fntName, size_t fntSize);
	protected:
		std::vector<std::unique_ptr<UILabel>> components;
		HorizontalAlign hTextAlign;
		VerticalAlign vTextAlign;
		HorizontalAlign hAlign;
		VerticalAlign vAlign;
		std::string fontName;
		size_t fontSize;
		SDL_Color bgColor;
		SDL_Color fgColor;
		bool autosize;
		SDL_Rect initPos;
		void UpdatePanel();
		void ItemChanged(UILabel* sender);
		void SizeChanged(UIComponent* sender) override;
	};

}

#endif //UIPANEL_H