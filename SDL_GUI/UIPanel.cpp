#include "UIPanel.h"

namespace SDL_GUI {

	UIPanel::UIPanel(SDL_Renderer* renderer, std::string name,
					 int x, int y, size_t w, size_t h, bool autosize, bool autofill,
					 std::string fontName, size_t fontSize,
					 HorizontalAlign hTextAlign, VerticalAlign vTextAlign, VerticalAlign vAlign,
					 SDL_Color bgColor, SDL_Color fgColor) :
			UIComponent(renderer, name, x, y, w, h, true) {
		this->bgColor = bgColor;
		this->fgColor = fgColor;
		this->autosize = autosize;
		this->autofill = autofill;
		this->fontName = fontName;
		this->fontSize = fontSize;
		this->hTextAlign = hTextAlign;
		this->vTextAlign = vTextAlign;
		this->vAlign = vAlign;
		initPos = rect;
		UpdatePanel();
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
	}

	void UIPanel::SetSize(size_t w, size_t h) {
		if(autosize)
			return;
		UIComponent::SetSize(w, h);
	}

	void UIPanel::AddItem(std::string name, std::string caption) {
		std::unique_ptr<UILabel> label = std::make_unique<UILabel>(renderer, name, caption, fontName, fontSize, rect.x, rect.y, rect.w, fontSize, true, hTextAlign, vTextAlign);
		label->OnTextChanged.AddListener(std::bind(&UIPanel::ItemChanged, this, std::placeholders::_1));
		label->SetAutosize(!autofill);
		label->SetColor(bgColor, fgColor);
		label->AlignHorizontal(hTextAlign);
		label->AlignVertical(vTextAlign);
		label->Show();
		components.push_back(move(label));
		UpdatePanel();
	}

	void UIPanel::RemoveItem(std::string name) {
		components.erase(std::remove_if(components.begin(), components.end(), [&](auto const& c) { return c->GetName() == name; }), components.end());
		UpdatePanel();
	}

	void UIPanel::ClearItems()
	{
		rect = initPos;
		if(components.size() > 0)
			components.clear();
	}

	void UIPanel::AlignTextHorizontal(HorizontalAlign hAlign) {
		this->hTextAlign = hAlign;
		for(auto& c : components) {
			c->AlignHorizontal(hAlign);
		}
	}

	void UIPanel::AlignTextVertical(VerticalAlign vAlign) {
		this->vTextAlign = vAlign;
		for(auto& c : components) {
			c->AlignVertical(vAlign);
		}
	}

	void UIPanel::AlignItems(VerticalAlign vAlign) {
		this->vAlign = vAlign;
		size_t totalHeight = 0;
		for(auto& c : components) {
			totalHeight += c->GetRect().h;
		}
		int cnt = 0;
		switch(vAlign) {
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

	void UIPanel::SetFont(std::string fntName, size_t fntSize) {
		for(auto& c : components) {
			c->SetFont(fntName, fntSize);
		}
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
		if(autofill) {
			for(auto& c : components) {
				c->SetWidth(rect.w);
			}
			AlignItems(vAlign);
		}
	}

	void UIPanel::ItemChanged(UILabel* sender) {
		UpdatePanel();
	}

	void UIPanel::SizeChanged(UIComponent* sender) {
		UpdatePanel();
	}

}
