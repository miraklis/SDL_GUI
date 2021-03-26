#include "UIPanel.h"

namespace SDL_GUI {

	UIPanel::UIPanel(SDL_Renderer* renderer, std::string name, int x, int y) 
			: UIComponent(renderer, name, x, y) {
		initPos = rect;
		hAlign = HorizontalAlign::Left;
		vAlign = VerticalAlign::Top;
	}

	UIPanel::~UIPanel() {
		ClearItems();
	}

	UILabel* UIPanel::operator[](size_t index) {
		if(index < 0 || index >= components.size())
			return nullptr;
		return components[index].get();
	}

	UILabel* UIPanel::operator[](std::string name) {
		if(components.size() == 0)
			return nullptr;
		for(auto& c : components) {
			if(c->GetName() == name)
				return c.get();
		}
		return nullptr;
	}

	void UIPanel::Render() {
		if(!visible)
			return;
		for(const auto& c : components) {
			c->Render();
		}
	}

	void UIPanel::SetPos(int x, int y) {
		UIComponent::SetPos(x, y);
		initPos.x = x;
		initPos.y = y;
		UpdatePanel();
	}

	void UIPanel::AddItem(std::unique_ptr<UILabel> newItem) {
		newItem->OnTextChanged.AddListener(std::bind(&UIPanel::ItemChanged, this, std::placeholders::_1));
		if(IsVisible())
			newItem->Show();
		components.push_back(move(newItem));
		UpdatePanel();
	}

	void UIPanel::RemoveItem(std::string name) {
		components.erase(std::remove_if(components.begin(), components.end(), [&](auto const& c) { return c->GetName() == name; }), components.end());
		UpdatePanel();
	}

	void UIPanel::ClearItems() {
		if(components.size() > 0)
			components.clear();
	}

	void UIPanel::SetHorizontalAlign(HorizontalAlign hAlign) {
		this->hAlign = hAlign;
		UpdatePanel();
	}

	void UIPanel::SetVerticalAlign(VerticalAlign vAlign) {
		this->vAlign = vAlign;
		UpdatePanel();
	}

	void UIPanel::Show() {
		UIComponent::Show();
		for(auto& c : components) {
			c->Show();
		}
	}

	void UIPanel::UpdatePanel() {
		size_t totalComponentHeight = 0;
		size_t maxComponentWidth = 0;
		for(auto& c : components) {
			SDL_Rect r = c->GetRect();
			totalComponentHeight += r.h;
			if(c->GetTextWidth() > maxComponentWidth)
				maxComponentWidth = c->GetTextWidth();
		}
		rect.w = maxComponentWidth;
		rect.h = totalComponentHeight;
		switch(hAlign) {
			case HorizontalAlign::Center:
				rect.x = initPos.x - (rect.w / 2);
				break;
			case HorizontalAlign::Right:
				rect.x = initPos.x - rect.w;
				break;
			default:
				rect.x = initPos.x;
		}
		switch(vAlign) {
			case VerticalAlign::Middle:
				rect.y = initPos.y - (rect.h / 2);
				break;
			case VerticalAlign::Bottom:
				rect.y = initPos.y - rect.h;
				break;
			default:
				rect.y = initPos.y;
		}
		int newY = rect.y;
		for(auto& c : components) {
			c->SetWidth(rect.w);
			c->SetPos(rect.x, newY);
			newY += c->GetRect().h;
		}
	}

	void UIPanel::ItemChanged(UILabel* sender) {
		UpdatePanel();
	}

}
