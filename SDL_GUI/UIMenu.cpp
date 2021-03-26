#include "UIMenu.h"

namespace SDL_GUI {

	UIMenu::UIMenu(SDL_Renderer* renderer, std::string name, int x, int y, std::shared_ptr<UIMenu> parent, std::function<bool(std::string)> callback)
			:UIPanel(renderer, name, x, y) {
		focus = false;
		upLimit = 0;
		selectedItem = 0;
		bgColor = selFGColor = { 0,0,0,255 };
		fgColor = selBGColor = { 255,255,255,255 };
		this->parent = parent;
		this->callback = callback;
	}

	UIMenu::~UIMenu() {
		upLimit = 0;
		selectedItem = 0;
		ClearItems();
	}

	void UIMenu::SetColor(SDL_Color bgColor, SDL_Color fgColor, SDL_Color selBGColor, SDL_Color selFGColor) {
		this->bgColor = bgColor;
		this->fgColor = fgColor;
		this->selBGColor = selBGColor;
		this->selFGColor = selFGColor;
		for(auto& c : components) {
			c->SetColor(bgColor, fgColor);
		}
		SelectItem(selectedItem);
	}

	std::shared_ptr<UIMenu> UIMenu::CreateSubMenu(std::string name) {
		return std::make_shared<UIMenu>(renderer, name, initPos.x, initPos.y, shared_from_this(), this->callback);
	}

	void UIMenu::HandleEvents() {
		if(!focus)
			return;
        SDL_Event event;
        SDL_PollEvent(&event);
		switch(event.type) {
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym) {
					case SDLK_UP:
						if(selectedItem > upLimit) {
							SelectItem(selectedItem - 1);
						}
						break;
					case SDLK_DOWN:
						if(selectedItem < components.size() - 1) {
							SelectItem(selectedItem + 1);
						}
						break;
					case SDLK_RETURN:
						callback(components[selectedItem]->GetName());
						break;
					case SDLK_ESCAPE:
						callback("esc");
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
		newItem->SetColor(bgColor, fgColor);
		UIPanel::AddItem(std::move(newItem));
		if(components.size() == 1) // if it is the first Item
			SelectItem(0); // select it
	}

	void UIMenu::SelectItem(size_t index) {
		if(components.size() == 0)
			return;
		if(index >= components.size())
			index = components.size() - 1;
		components[selectedItem]->SetColor(bgColor, fgColor);
		selectedItem = index;
		components[selectedItem]->SetColor(selBGColor, selFGColor);
	}

	void UIMenu::SetFocus(bool focus) {
		this->focus = focus;
	}

	std::shared_ptr<UIMenu> UIMenu::GetParent() {
		return parent;
	}

}