#include "UIMenu.h"
#include "UILabel.h"

namespace SDL_GUI {

	UIMenu::UIMenu(SDL_Renderer* renderer, std::string name, int x, int y, std::shared_ptr<UIMenu> parent, std::function<bool(std::string)> callback)
			:UIPanel(renderer, name, x, y) {
		_focus = false;
		_upLimit = 0;
		_selectedItem = 0;
		_selFGColor = { 0,0,0,255 };
		_selBGColor = { 255,255,255,255 };
		_parent = parent;
		_callback = callback;
	}

	UIMenu::~UIMenu() {
		_upLimit = 0;
		_selectedItem = 0;
		ClearItems();
	}

	void UIMenu::SetDefaultColors(SDL_Color bgColor, SDL_Color fgColor, SDL_Color selBGColor, SDL_Color selFGColor) {
		UIPanel::SetDefaultColors(bgColor, fgColor);
		_selBGColor = selBGColor;
		_selFGColor = selFGColor;
		for(auto& c : _components) {
			c->SetColor(bgColor, fgColor);
		}
		SelectItem(_selectedItem);
	}

	std::shared_ptr<UIMenu> UIMenu::CreateSubMenu(std::string name) {
		return std::make_shared<UIMenu>(_renderer, name, _initPos.x, _initPos.y, shared_from_this(), _callback);
	}

	void UIMenu::HandleEvents() {
		if(!_focus)
			return;
        SDL_Event event;
        SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						if(_selectedItem > _upLimit) {
							SelectItem(_selectedItem - 1);
						}
						break;
					case SDLK_DOWN:
						if(_selectedItem < _components.size() - 1) {
							SelectItem(_selectedItem + 1);
						}
						break;
					case SDLK_RETURN:
						_callback(_components[_selectedItem]->GetName());
						break;
					case SDLK_ESCAPE:
						_callback("esc");
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	void UIMenu::AddItem(std::unique_ptr<UILabel> newItem) {
		newItem->SetColor(_defaultBGColor, _defaultFGColor);
		UIPanel::AddItem(std::move(newItem));
		if(_components.size() == 1) // if it is the first Item
			SelectItem(0); // select it
	}

	void UIMenu::AddItem(std::string name, std::string caption)
	{
		UIPanel::AddItem(name, caption);
	}

	void UIMenu::SelectItem(size_t index) {
		if(_components.size() == 0)
			return;
		if(index >= _components.size())
			index = _components.size() - 1;
		_components[_selectedItem]->SetColor(_defaultBGColor, _defaultFGColor);
		_selectedItem = index;
		_components[_selectedItem]->SetColor(_selBGColor, _selFGColor);
	}

	void UIMenu::SetFocus(bool focus) {
		_focus = focus;
	}

	std::shared_ptr<UIMenu> UIMenu::GetParent() {
		return _parent;
	}

}