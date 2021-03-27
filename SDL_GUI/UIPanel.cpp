#include "UIPanel.h"
#include "UILabel.h"
#include "UIInputBox.h"

namespace SDL_GUI {

	UIPanel::UIPanel(SDL_Renderer* renderer, std::string name, int x, int y) 
			: UIComponent(name, x, y, 0, 0) {
		_renderer = renderer;
		_initPos = _rect;
		_hAlign = HorizontalAlign::Left;
		_vAlign = VerticalAlign::Top;
		_defaultHorAlign = HorizontalAlign::Left;
		_defaultVerAlign = VerticalAlign::Top;
		_defaultFontName = sFonts::TTF_TIMES;
		_defaultFontSize = 16;
		_defaultBGColor = { 0,0,0,255 };
		_defaultFGColor = { 255,255,255,255 };
	}

	UIPanel::~UIPanel() {
		ClearItems();
	}

	UITextComponent* UIPanel::operator[](size_t index) {
		if(index < 0 || index >= _components.size())
			return nullptr;
		return _components[index].get();
	}

	UITextComponent* UIPanel::operator[](std::string name) {
		if(_components.size() == 0)
			return nullptr;
		for(auto& c : _components) {
			if(c->GetName() == name)
				return c.get();
		}
		return nullptr;
	}

	void UIPanel::Render() {
		if(!_visible)
			return;
		for(const auto& c : _components) {
			c->Render();
		}
	}

	void UIPanel::SetPos(int x, int y) {
		UIComponent::SetPos(x, y);
		_initPos.x = x;
		_initPos.y = y;
		updatePanel();
	}

	void UIPanel::AddItem(std::unique_ptr<UITextComponent> newItem) {
		newItem->OnTextChanged.AddListener(std::bind(&UIPanel::itemChanged, this, std::placeholders::_1));
		if(_visible)
			newItem->Show();
		_components.push_back(std::move(newItem));
		updatePanel();
	}

	void UIPanel::AddLabel(std::string name, std::string caption) {
		std::unique_ptr<UILabel> item = std::make_unique<UILabel>(
			_renderer, name, caption, 0, 0, 0, 0, false,
			_defaultFontName, _defaultFontSize,	_defaultBGColor, _defaultFGColor, _defaultHorAlign, _defaultVerAlign);
		AddItem(std::move(item));
	}

	void UIPanel::AddInputBox(std::string name)
	{
		std::unique_ptr<UIInputBox> item = std::make_unique<UIInputBox>(
			_renderer, name, "", 0, 0, 0, 0, false,
			_defaultFontName, _defaultFontSize, _defaultBGColor, _defaultFGColor, _defaultHorAlign, _defaultVerAlign);
		AddItem(std::move(item));
	}

	void UIPanel::RemoveItem(std::string name) {
		_components.erase(std::remove_if(_components.begin(), _components.end(), [&](auto const& c) { return c->GetName() == name; }), _components.end());
		updatePanel();
	}

	void UIPanel::ClearItems() {
		if(_components.size() > 0)
			_components.clear();
	}

	void UIPanel::SetHorizontalAlign(HorizontalAlign hAlign) {
		_hAlign = hAlign;
		updatePanel();
	}

	void UIPanel::SetVerticalAlign(VerticalAlign vAlign) {
		_vAlign = vAlign;
		updatePanel();
	}

	void UIPanel::SetDefaultHorAlign(HorizontalAlign hAlign) {
		_defaultHorAlign = hAlign;
	}

	void UIPanel::SetDefaultVerAlign(VerticalAlign vAlign) {
		_defaultVerAlign = vAlign;
	}

	void UIPanel::SetDefaultFont(std::string fontName, size_t fontSize) {
		_defaultFontName = fontName;
		_defaultFontSize = fontSize;
	}

	void UIPanel::SetDefaultColors(SDL_Color& bgColor, SDL_Color fgColor) {
		_defaultBGColor = bgColor;
		_defaultFGColor = fgColor;
	}

	void UIPanel::Show() {
		UIComponent::Show();
		for(auto& c : _components) {
			c->Show();
		}
	}

	void UIPanel::updatePanel() {
		size_t totalComponentHeight = 0;
		size_t maxComponentWidth = 0;
		for(auto& c : _components) {
			SDL_Rect r = c->GetRect();
			totalComponentHeight += r.h;
			if(c->GetTextWidth() > maxComponentWidth)
				maxComponentWidth = c->GetTextWidth();
		}
		_rect.w = maxComponentWidth;
		_rect.h = totalComponentHeight;
		switch(_hAlign) {
			case HorizontalAlign::Center:
				_rect.x = _initPos.x - (_rect.w / 2);
				break;
			case HorizontalAlign::Right:
				_rect.x = _initPos.x - _rect.w;
				break;
			default:
				_rect.x = _initPos.x;
		}
		switch(_vAlign) {
			case VerticalAlign::Middle:
				_rect.y = _initPos.y - (_rect.h / 2);
				break;
			case VerticalAlign::Bottom:
				_rect.y = _initPos.y - _rect.h;
				break;
			default:
				_rect.y = _initPos.y;
		}
		int newY = _rect.y;
		for(auto& c : _components) {
			c->SetWidth(_rect.w);
			c->SetPos(_rect.x, newY);
			newY += c->GetRect().h;
		}
	}

	void UIPanel::itemChanged(UITextComponent* sender) {
		updatePanel();
	}

}
