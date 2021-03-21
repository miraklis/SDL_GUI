#include "UIPanel.h"

namespace SDL_GUI {

	UIPanel::UIPanel(SDL_Renderer* renderer, std::string name,
					 int x, int y, size_t w, size_t h, bool autosize,
					 std::string fontName, size_t fontSize,
					 HorizontalAlign hAlign, VerticalAlign vAlign,
					 SDL_Color bgColor, SDL_Color fgColor) :
			UIComponent(renderer, name, x, y, w, h, true) {
		this->bgColor = bgColor;
		this->fgColor = fgColor;
		this->autosize = autosize;
		this->fontName = fontName;
		this->fontSize = fontSize;
		this->hAlign = hAlign;
		this->vAlign = vAlign;
		this->hTextAlign = HorizontalAlign::Left;
		this->vTextAlign = VerticalAlign::Top;
		initPos = rect;
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
		SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
		SDL_RenderFillRect(renderer, &rect);
		for(const auto& c : components) {
			c->Render();
		}
	}

	void UIPanel::SetPos(int x, int y) {
		int deltaX = x - rect.x;
		int deltaY = y - rect.y;
		for(auto& c : components) {
			SDL_Rect p = c->GetRect();
			c->SetPos(p.x + deltaX, p.y + deltaY);
		}
		UIComponent::SetPos(x, y);
		initPos.x = x;
		initPos.y = y;
		AlignHorizontal(hAlign);
		AlignVertical(vAlign);
		UpdatePanel();
	}

	void UIPanel::SetSize(size_t w, size_t h) {
		if(autosize)
			return;
		UIComponent::SetSize(w, h);
	}

	void UIPanel::AddItem(std::string name, std::string caption) {
		std::unique_ptr<UILabel> label = std::make_unique<UILabel>(renderer, name, caption, fontName, fontSize, rect.x, rect.y, rect.w, fontSize, true, hAlign, VerticalAlign::Middle);
		label->OnTextChanged.AddListener(std::bind(&UIPanel::ItemChanged, this, std::placeholders::_1));
		label->SetAutosize(false);
		label->SetColor(bgColor, fgColor);
		label->AlignHorizontal(hTextAlign);
		label->AlignVertical(vTextAlign);
		label->Show();
		components.push_back(move(label));
		AlignTextHorizontal(hTextAlign);
		AlignTextVertical(vTextAlign);
		AlignHorizontal(hAlign);
		AlignVertical(vAlign);
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

	void UIPanel::AlignTextHorizontal(HorizontalAlign hTextAlign) {
		this->hTextAlign = hTextAlign;		
		for(auto& c : components) {
			c->AlignHorizontal(hTextAlign);
		}
	}

	void UIPanel::AlignTextVertical(VerticalAlign vTextAlign) {
		this->vTextAlign = vTextAlign;
		for(auto& c : components) {
			c->AlignVertical(vTextAlign);
		}
		size_t totalHeight = 0;
		for(auto& c : components) {
			totalHeight += c->GetRect().h;
		}
		int cnt = 0;
		switch(vTextAlign) {
			case VerticalAlign::Top:
				for(auto& c : components) {
					SDL_Rect r = c->GetRect();
					c->SetY(rect.y + (cnt * (r.h)));
					cnt++;
				}
				break;
			case VerticalAlign::Middle:
				for(auto& c : components) {
					SDL_Rect r = c->GetRect();
					c->SetY(rect.y + (rect.h / 2) - (totalHeight / 2) + (cnt * r.h));
					cnt++;
				}
				break;
			case VerticalAlign::Bottom:
				for(auto& c : components) {
					SDL_Rect r = c->GetRect();
					c->SetY(rect.y + rect.h - totalHeight + (cnt * r.h));
					cnt++;
				}
				break;
		}
	}

	void UIPanel::AlignHorizontal(HorizontalAlign hAlign) {
		this->hAlign = hAlign;		
		switch(hAlign) {
			case HorizontalAlign::Left:
				rect.x = initPos.x;
				break;
			case HorizontalAlign::Center:
				rect.x = initPos.x - (rect.w / 2);
				break;
			case HorizontalAlign::Right:
				rect.x = initPos.x - rect.w;
				break;
		}
		for(auto& c : components) {
			c->SetX(rect.x);
		}
	}

	void UIPanel::AlignVertical(VerticalAlign vAlign) {
		this->vAlign = vAlign;
		int oldY = rect.y;
		switch(vAlign) {
			case VerticalAlign::Top:
				rect.y = initPos.y;
				break;
			case VerticalAlign::Middle:
				rect.y = initPos.y - (rect.h / 2);
				break;
			case VerticalAlign::Bottom:
				rect.y = initPos.y - rect.h;
				break;
		}
		int deltaY = rect.y - oldY;
		for(auto& c : components) {
			SDL_Rect p = c->GetRect();
			c->SetY(p.y + deltaY);
		}
	}

	void UIPanel::SetFont(std::string fntName, size_t fntSize) {
		for(auto& c : components) {
			c->SetFont(fntName, fntSize);
		}
		UpdatePanel();
	}

	void UIPanel::UpdatePanel() {
		if(autosize) {
			size_t totalComponentHeight = 0;
			size_t maxComponentWidth = 0;
			for(auto& c : components) {
				SDL_Rect r = c->GetRect();
				totalComponentHeight += r.h;
				if(r.w > maxComponentWidth)
					maxComponentWidth = r.w;
			}
			rect.w = maxComponentWidth;
			rect.h = totalComponentHeight;
		}
		for(auto& c : components) {
			c->SetWidth(rect.w);
		}
	}

	void UIPanel::ItemChanged(UILabel* sender) {
		UpdatePanel();
	}

	void UIPanel::SizeChanged(UIComponent* sender) {
		UpdatePanel();
	}

}
