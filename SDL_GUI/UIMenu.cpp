#include "UIMenu.h"

namespace SDL_GUI {

	UIMenu::UIMenu(SDL_Renderer* renderer, std::string name, int x, int y, size_t w, size_t h, 
				   std::string fontName, size_t fontSize,
				   HorizontalAlign hTextAlign, VerticalAlign vTextAlign, VerticalAlign vAlign,
				   SDL_Color bgColor, SDL_Color fgColor, SDL_Color selBGColor, SDL_Color selFGColor,
				   std::shared_ptr<UIMenu> parent, std::function<bool(std::string)> callback) :
			UIPanel(renderer, name, x, y, w, h, true, true, fontName, fontSize, hTextAlign, vTextAlign, vAlign, bgColor, fgColor) {
		this->selBGColor = selBGColor;
		this->selFGColor = selFGColor;
		this->parent = parent;
		this->callback = callback;
		upLimit = 0;
		selectedItem = 0;
	}

	UIMenu::~UIMenu() {
		selectedItem = 0;
		ClearItems();
	}

	std::shared_ptr<UIMenu> UIMenu::CreateSubMenu(std::string name) {
		return std::make_shared<UIMenu>(renderer, name, rect.x, rect.y, rect.w, rect.y,
										fontName, fontSize, hTextAlign, vTextAlign, vAlign,
										bgColor, fgColor, selBGColor, selFGColor, shared_from_this());
	}

	void UIMenu::HandleEvents() {
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
					default:
						break;
				}
				break;
			default:
				break;
		}
	}

	void UIMenu::AddItem(std::string name, std::string caption) {
		UIPanel::AddItem(name, caption);
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

	std::shared_ptr<UIMenu> UIMenu::GetParent() {
		return parent;
	}

}