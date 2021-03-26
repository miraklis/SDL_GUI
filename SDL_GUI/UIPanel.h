#ifndef UIPANEL_H
#define UIPANEL_H

#include "UIMain.h"
#include "UIComponent.h"
#include "UILabel.h"

namespace SDL_GUI {

	class UIPanel : public UIComponent {
	public:
		UIPanel(SDL_Renderer* renderer, std::string name, int x, int y);
		virtual ~UIPanel() override;
		UILabel* operator[](size_t index);
		UILabel* operator[](std::string name);
		void Render() override;
		void SetPos(int x, int y) override;
		void Show() override;
		virtual void AddItem(std::unique_ptr<UILabel> newItem);
		void RemoveItem(std::string name);
		void ClearItems();
		void SetHorizontalAlign(HorizontalAlign hAlign);
		void SetVerticalAlign(VerticalAlign vAlign);
	protected:
		std::vector<std::unique_ptr<UILabel>> components;
		SDL_Rect initPos;
		HorizontalAlign hAlign;
		VerticalAlign vAlign;
		void UpdatePanel();
		void ItemChanged(UILabel* sender);
	};

}

#endif //UIPANEL2_H