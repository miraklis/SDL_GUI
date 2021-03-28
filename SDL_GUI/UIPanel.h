#ifndef UIPANEL_H
#define UIPANEL_H

#include "UIMain.h"
#include "UIComponent.h"
#include "UILabel.h"

namespace SDL_GUI {

	class UIPanel : public UIComponent 
	{
	public:
		UIPanel(SDL_Renderer* renderer, std::string name, int x, int y);
		virtual ~UIPanel() override;
		UITextComponent* operator[](size_t index);
		UITextComponent* operator[](std::string name);
		void Render() override;
		void SetPos(int x, int y) override;
		void Show() override;
		virtual void AddItem(std::unique_ptr<UILabel> newItem);
		virtual void AddItem(std::string name, std::string caption);
		void RemoveItem(std::string name);
		void ClearItems();
		void SetHorizontalAlign(HorizontalAlign hAlign);
		void SetVerticalAlign(VerticalAlign vAlign);
		void SetDefaultHorAlign(HorizontalAlign hAlign);
		void SetDefaultVerAlign(VerticalAlign vAlign);
		void SetDefaultFont(std::string fontName, size_t fontSize);
		void SetDefaultColors(SDL_Color& bgColor, SDL_Color& fgColor);
	protected:
		std::vector<std::unique_ptr<UILabel>> _components;
		bool _autosize;
		SDL_Rect _initPos;
		HorizontalAlign _hAlign;
		VerticalAlign _vAlign;
		HorizontalAlign _defaultHorAlign;
		VerticalAlign _defaultVerAlign;
		std::string _defaultFontName;
		size_t _defaultFontSize;
		SDL_Color _defaultBGColor;
		SDL_Color _defaultFGColor;
		void updatePanel();
		void itemChanged(UILabel *sender);
	};

}

#endif //UIPANEL2_H